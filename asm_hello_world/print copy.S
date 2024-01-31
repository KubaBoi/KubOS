rng_print:
    rdtsc

    movzx eax, al
    mov bl, 0x0a
    div bl

    add ah, 0x30
    mov al, ah
    call print_al
    ret

print_al:    
    mov ah, 0x0e
    int 0x10
    ret