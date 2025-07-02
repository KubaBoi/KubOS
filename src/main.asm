org 0x7c00 ; Boot sector starts at 0x7c00 (directive)
bits 16 ; Use 16-bit mode (directive)

; macro for new line
%define ENDL 0x0d, 0x0a

start:
    jmp main

; Prints a string to the screen
; Params:
;   - ds:si points to string
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
    mov ax, 0 ; cant write to ds/es directly
    mov ds, ax
    mov es, ax

    ; setup stack
    mov ss, ax
    mov sp, 0x7c00 ; address to start of system so stack would not overwrite it

    ; print message
    mov si, msg_hello
    call puts

    hlt

.halt:
    jmp .halt 

msg_hello: db "Hello world", ENDL, 0

; $ is the current position in the code
; $$ is the start of the code segment (0x7c00)
times 510 - ($ - $$) db 0 ; Fill the rest of the boot sector with zeros
dw 0xAA55 ; Boot sector signature (0xAA55)