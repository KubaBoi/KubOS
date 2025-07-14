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
bpb_dir_entries:            dw 0x0e0        ; 224
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
ebr_volume_id:              db 0x3e, 0x97, 0xb6, 0xe8   ; sn
ebr_label_string:           db "KUBOS 0.1  "            ; 11 bytes (padded with spaces)
ebr_system_id:              db "FAT12   "               ; 8 bytes (padded with spaces)

;
; CODE
;

start:
    ; setup data segments
    mov ax, 0                   ; cant write to ds/es directly
    mov ds, ax
    mov es, ax

    ; setup stack
    mov ss, ax
    mov sp, 0x7c00              ; address to start of system so stack would not overwrite it

    ; some bioses might start us at 07c0:0000 instead of 0000:7c00
    ; may be => jmp 0x0000:.after
    push es
    push word .after
    retf

.after:
    
    ; read something from floppy disk
    ; bios should set dl to drive number
    mov [ebr_drive_number], dl

    ; show loading message
    mov si, msg_loading
    call puts

    ; read drive parameters (sectors per track and head count),
    ; instead of relying on data on formatted disk
    push es
    mov ah, 08h                     ; Get Drive Parameters
    int 13h
    jc floppy_error
    pop es

    and cl, 0x3f                    ; remove top 2 bits
    xor ch, ch
    mov [bpb_sectors_per_track], cx ; sector count

    inc dh
    mov [bpb_heads], dh             ; head count

    ; compute LBA of root directory = reserved * fats * sectors_per_fat
    mov ax, [bpb_sectors_per_fat]
    mov bl, [bpb_fat_count]
    xor bh, bh
    mul bx                          ; ax = (fats * sectors_per_fat)
    add ax, [bpb_reserved_sectors]  ; ax = LBA of root directory
    push ax

    ; compute size of root directory = (32 * number_of_entries) / bytes_per_sector
    mov ax, [bpb_dir_entries]   
    shl ax, 5                       ; ax *= 32
    xor dx, dx
    div word [bpb_bytes_per_sector] ; numbers of sectors we need to read

    test dx, dx                     ; if dx != 0, add 1
    jz .root_dir_after
    inc ax                          ; division remainder != 0, add 1
                                    ; this means we have a sector only partially filled with entries

.root_dir_after:

    ; read root directory
    mov cl, al                      ; cl = number of sectors to read = size of root directory
    pop ax                          ; ax = LBA of root directory
    mov dl, [ebr_drive_number]      ; dl = drive number (we saved it previously)
    mov bx, buffer                  ; es:bx = buffer
    call disk_read

    ; search for kernel.bin
    xor bx, bx
    mov di, buffer

.search_kernel:
    mov si, file_kernel_bin         ; file name
    mov cx, 11                      ; compare up to 11 characters
    push di
    repe cmpsb                      ; cmpsb compares two bytes located in memory at addresses ds:si and es:di
                                    ; repe repeats a string instruction while the operands are equal (zero flag = 1)
                                    ; or until cx reaches 0
    pop di
    je .found_kernel
    
    add di, 32
    inc bx
    cmp bx, [bpb_dir_entries]
    jl .search_kernel

    ; kernel not found
    jmp kernel_not_found_error

.found_kernel:

    ; di should have the address to the entry
    mov ax, [di + 26]               ; first logical cluster field (offset 26)
    mov [kernel_cluster], ax

    ; load Field Allocation Table from disk into memory
    mov ax, [bpb_reserved_sectors]
    mov bx, buffer
    mov cl, [bpb_sectors_per_fat]
    mov dl, [ebr_drive_number]
    call disk_read

    ; read kernel and process FAT chain
    mov bx, KERNEL_LOAD_SEGMENT
    mov es, bx
    mov bx, KERNEL_LOAD_OFFSET

.load_kernel_loop:

    ; read next cluster
    mov ax, [kernel_cluster]
    add ax, 31                      ; first cluster = (kernel_cluster - 2) * sectors_per_cluster + start_sector
                                    ; start sector = reserved + fats + root_directory_size = 1 + 18 + 134 = 33
    mov cl, 1
    mov dl, [ebr_drive_number]
    call disk_read

    ; add will overflow if kernel.bin will be larger than 64kb
    add bx, [bpb_bytes_per_sector]

    ; compute location of next cluster
    mov ax, [kernel_cluster]
    mov cx, 3
    mul cx
    mov cx, 2
    div cx                          ; ax = index of entry in FAT, dx = cluster mod 2

    mov si, buffer
    add si, ax
    mov ax, [ds:si]                 ; read entry from FAT table at index ax

    or dx, dx
    jz .even

.odd:
    shr ax, 4
    jmp .next_cluster_after

.even:
    and ax, 0x0fff

.next_cluster_after:
    cmp ax, 0x0ff8                  ; end of chain
    jae .read_finish

    mov [kernel_cluster], ax
    jmp .load_kernel_loop

.read_finish:
    
    ; jump to kernel
    mov dl, [ebr_drive_number]      ; boot device in dl

    mov ax, KERNEL_LOAD_SEGMENT
    mov ds, ax
    mov es, ax

    jmp KERNEL_LOAD_SEGMENT:KERNEL_LOAD_OFFSET

    jmp wait_key_and_reboot         ; should never happen

    cli             ; disable interrupts, this way CPU cant get out of "halt" state
    hlt

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

;
; Error handlers
;

floppy_error:
    mov si, msg_read_failed
    call puts
    jmp wait_key_and_reboot

kernel_not_found_error:
    mov si, msg_kernel_not_found
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


msg_loading:              db "Loading...", ENDL, 0
msg_read_failed:        db "Read from disk failed!", ENDL, 0
msg_kernel_not_found:   db "Kernel file not found", ENDL, 0
file_kernel_bin:        db "KERNEL  BIN"
kernel_cluster:         dw 0

; segment and offset where kernel will be loaded in real mode
; 0x7e00 to 0x7ffff is Conventional memory in real mode address space (480.5 KiB)
KERNEL_LOAD_SEGMENT     equ 0x2000 ; 0x2000:0000 = 0x20000 physical address
KERNEL_LOAD_OFFSET      equ 0

; $ is the current position in the code
; $$ is the start of the code segment (0x7c00)
times 510 - ($ - $$) db 0 ; Fill the rest of the boot sector with zeros
dw 0xAA55 ; Boot sector signature (0xAA55)

buffer:
