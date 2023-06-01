    jmp main

%include "lib/io.asm"
main:
    mov ax, 0x07C0
    mov ds, ax
    cld
    
    mov si, msg
    call bios_print
 
hang:
    jmp hang
 
    msg   db 'Hello World', 13, 10, 0
    times 510-($-$$) db 0
    db 0x55
    db 0xAA