init_keyhndl:
    cli      ;no interruptions
    mov bx, 0x09   ;hardware interrupt #
    shl bx, 2   ;multiply by 4
    xor ax, ax
    mov gs, ax   ;start of memory
    mov [gs:bx], word keyhndl
    mov [gs:bx+2], ds ; segment
    sti
    ret

keyhndl:
    in al, 0x60   ; get key data
    mov bl, al   ; save it
    mov byte [port60], al
    
    in al, 0x61   ; keybrd control
    mov ah, al
    or al, 0x80   ; disable bit 7
    out 0x61, al   ; send it back
    xchg ah, al   ; get original
    out 0x61, al   ; send that back
    
    mov al, 0x20   ; End of Interrupt
    out 0x20, al   ;
    
    and bl, 0x80   ; key released
    jnz keyhndl__done   ; don't repeat
    
    mov al, '#'
    call cprint
    mov ax, [port60]
    mov  word [reg16], ax
    call printreg16
 
    keyhndl__done:
        iret