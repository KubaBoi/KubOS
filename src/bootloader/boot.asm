org 0x7c00 ; Boot sector starts at 0x7c00 (directive)
bits 16 ; Use 16-bit mode (directive)

; macro for new line
%define ENDL 0x0d, 0x0a

;
; FAT12 header
; https://wiki.osdev.org/FAT (BPB)
;
jmp short start
nop

bpb_oem:                    db "MSWIN4.1"   ; could be any 8 bytes but microsoft recommends this
bpb_bytes_per_sector:       dw 512          ; 00 02 in little endian is 512 (from hexedit)
bpb_sectors_per_cluster:    db 1            
bpb_reserved_sectors:       dw 1
bpb_fat_count:              db 2
bpb_dir_entries:            dw 0x0e0
bpb_total_sectors:          dw 2880         ; 2880 * 512 = 1.44MB (2880d = b40)
bpb_media_descriptor_type:  db 0x0f0        ; F0h = 3.5" floppy disk
bpb_sectors_per_fat:        dw 9            ; 2 bytes
bpb_sectors_per_track:      dw 0x12         ; 12h = 18d
bpb_heads:                  dw 2
bpb_hidden_sectors:         dd 0            ; 4 bytes
bpb_large_sector_count:     dd 0            ; 4 bytes

; Extended boot record
ebr_drive_number:           db 0
ebr_flags_reserved:         db 0
ebr_signature:              db 0x29
ebr_volumen_id:             db 0x3e, 0x97, 0xb6, 0xe8   ; sn
ebr_label_string:           db "KUBOS 0.1  "            ; 11 bytes (padded with spaces)
ebr_system_id:              db "FAT12   "               ; 8 bytes (padded with spaces)

;
; CODE
;

start:
    jmp main

;
; Prints a string to the screen
; Params:
;   - ds:si points to string
;
puts:
    push si
    push ax

.loop:
    lodsb           ; loads next char in al and increments si
    or al, al       ; verify if next char in null
    jz .done        ; if next char in null, jump out of the .loop

    mov ah, 0x0e    ; set mode to "Write Character in TTY Mode"
    xor bh, bh      ; reset page number to zero
    ; bl - foreground pixel color (graphics mode)
    int 0x10        ; video service interrupt
    jmp .loop

.done:
    pop ax
    pop si
    ret

main:

    ; setup data segments
    mov ax, 0                   ; cant write to ds/es directly
    mov ds, ax
    mov es, ax

    ; setup stack
    mov ss, ax
    mov sp, 0x7c00              ; address to start of system so stack would not overwrite it

    ; read something from floppy disk
    ; bios should set dl to drive number
    mov [ebr_drive_number], dl

    mov ax, 1                   ; LBA=1, second sector from disk
    mov cl, 1                   ; 1 sector to read
    mov bx, 0x7e00              ; data should be after the bootloader
    call disk_read

    ; print message
    mov si, msg_hello
    call puts

    cli             ; disable interrupts, this way CPU cant get out of "halt" state
    hlt

;
; Error handlers
;

floppy_error:
    mov si, msg_read_failed
    call puts
    jmp wait_key_and_reboot

wait_key_and_reboot:
    mov ah, 0
    int 16h         ; wait for keypress
    jmp 0ffffh:0    ; jump to beginning of bios, should reboot

.halt:
    cli             ; disable interrupts, this way CPU cant get out of "halt" state
    hlt

;
; Disk routines
;

;
; Converts an LBA address to a CHS address
; Parameters:
;   - ax: LBA address
; Returns:
;   - cx [bits 0-5]: sector number
;   - cx [bits 6-15]: cylinder
;   - dh: head
;
lba_to_chs:
    push ax
    push dx

    xor dx, dx
    div word [bpb_sectors_per_track]    ; ax = LBA / SectorsPerTrack
                                        ; dx = LBA % SectorsPerTrack
    inc dx                              ; dx = (LBA % SectorsPerTrack + 1) = sector
    mov cx, dx                          ; cx = sector

    xor dx, dx
    div word [bpb_heads]                ; ax = (LBA / SectorsPerTrack) / Heads = cylinder
                                        ; dx = (LBA / SectorsPerTrack) % Heads = head
    mov dh, dl                          ; dh = head
    mov ch, al                          ; ch = cylinder (lower 8 bits)
    shl ah, 6                           
    or cl, ah                           ; put upper 2 bits of cylinder in cl

    pop ax
    mov dl, al                          ; restore dl
    pop ax
    ret

;
; Reads sectors from a disk
; Parameters:
;   - ax: LBA address
;   - cl: number of sectors to read (up to 128)
;   - dl: drive number
;   - es:bx: memory address where to store read data
;
disk_read:
    push ax                 ; save modified registers
    push bx
    push cx
    push dx
    push di

    push cx                 ; temporarily save cl (number of sectors to read)
    call lba_to_chs         ; compute CHS
    pop ax                  ; AL = number of sectors to read

    mov ah, 02h             ; Read sectors
    mov di, 3               ; retry count (floppy disks are unrealiable)

.retry:
    pusha                   ; save all registers, we dont know what bios modifies
    stc                     ; set carry flag, some bioses dont set it
    int 13h                 ; Low level disk services (carry flag cleared = success)
    jnc .done               ; jump if carry not set

    ; read failed
    popa
    call disk_reset

    dec di
    test di, di
    jnz .retry

.fail:
    ; all attempts are exhausted
    jmp floppy_error

.done:
    popa

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

;
; Resets disk controller
; Parameters:
;   - dl: drive number
;
disk_reset:
    pusha
    mov ah, 0
    stc
    int 13h
    jc floppy_error
    popa
    ret


msg_hello:          db "Hello world", ENDL, 0
msg_read_failed:    db "Read from disk failed!", ENDL, 0
msg_test:           db "Test", ENDL, 0

; $ is the current position in the code
; $$ is the start of the code segment (0x7c00)
times 510 - ($ - $$) db 0 ; Fill the rest of the boot sector with zeros
dw 0xAA55 ; Boot sector signature (0xAA55)