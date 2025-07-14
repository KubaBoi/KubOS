org 0x0 
bits 16 

; macro for new line
%define ENDL 0x0d, 0x0a

start:
    ; print message
    mov si, msg_hello
    call puts

.halt:
    cli
    hlt

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

msg_hello: db "Hello world from KERNEL!!!!", ENDL, 0