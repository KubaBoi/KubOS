.code16


    jmp _start

%include "print copy.S"

_start:
    cli
    mov esi, msg
    mov ah, 0x0e
loop:
    mov al, '-'
    int 0x10
    lodsb
    test al, al
    jz halt
    int 0x10
    mov al, '-'
    int 0x10 
    jmp loop
halt:
    call rng_print
    call rng_print
    mov al, 0x25
    call print_al
    hlt

msg db "Tvoje gayovitos: ", 0x0, 0x0