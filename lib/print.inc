; Print string from SI
bios_print:
    lodsb
    or al, al  ;zero=end of str
    jz done    ;get out
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp bios_print
done:
    ret

;-----------------------------------------------
dochar:   
    call cprint  
    jmp sprint    
newline:
    add byte [ypos], 1
    mov byte [xpos], 0 
; Print string from SI 
; ES need to be set to 0xb800 
sprint:   
    lodsb      ; string char to AL
    cmp al, 10
    je newline
    cmp al, 0
    jne dochar   ; else, we're done
    ret
 
; Print one character from AL
cprint:   
    mov ah, 0x0F   ; attrib = black on white
    mov cx, ax    ; save char/attribute
    movzx ax, byte [ypos]
    mov dx, 160   ; 2 bytes (char/attrib)
    mul dx      ; for 80 columns, AX is used as multiplicant and result
    movzx bx, byte [xpos]
    shl bx, 1    ; times 2 to skip attrib
    
    mov di, 0        ; start of video memory
    add di, ax      ; add y offset
    add di, bx      ; add x offset
    
    mov ax, cx        ; restore char/attribute
    stosw              ; write char/attribute
    add byte [xpos], 1  ; advance to right
    
    ret
;-----------------------------------------------

; Print 4 bytes of `reg16` variable
; `mov word [reg16], ax`
printreg16:
    mov di, outstr16
    mov ax, [reg16]
    mov si, hexstr
    mov cx, 4   ;four places
hexloop:
    rol ax, 4   ;leftmost will
    mov bx, ax   ; become
    and bx, 0x0f   ; rightmost
    mov bl, [si + bx];index into hexstr
    mov [di], bl
    inc di
    dec cx
    jnz hexloop
    mov si, outstr16
    call sprint
    
    ret
;-----------------------------------------------

clear:
    mov ax, 0xb800 
    mov es, ax 
    mov al, 0 
    mov ah, 0x0F
    xor cx, cx

    clear_loop:
        xor di, di
        add di, cx
        stosw
        add cx, 2
        cmp cx, VIDEO_MEM_SZ
        jle clear_loop
    ret
;-----------------------------------------------

hexstr   db '0123456789ABCDEF'
outstr16   db '0000', 0  ;register value string
reg16   dw    0  ; pass values to printreg16
VIDEO_MEM_SZ equ 3999 ; cannot be more coz fall