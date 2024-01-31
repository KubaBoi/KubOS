.code16

.text

    jmp _start

#include "print.S"

_start:
    mov $msg, %si
    mov $0x0e, %ah
loop:
    lodsb
    test %al, %al
    je halt
    int $0x10 
    jmp loop
halt:
    call rng_print
    call rng_print
    mov $0x25, %al
    call print_al
    hlt

msg:
    .asciz "Tvoje gayovitos: "