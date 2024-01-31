rng_print:
    rdtsc

    movzx %al, %ax
    mov $0x0a, %bl
    div %bl

    add $0x30, %ah
    mov %ah, %al
    call print_al
    ret

print_al:    
    mov $0x0e, %ah
    int $0x10
    ret