; Print string from SI
bios_print:
    lodsb
    or al, al  ;zero=end of str
    jz bios_print_done    ;get out
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp bios_print
bios_print_done:
    ret

;-----------------------------------------------
dochar:   
    call cprint  
    jmp sprint    
newline:
    mov ax, [cursor]
    mov cx, SCREEN_WIDTH
    xor dx, dx
    div cx ; dx is modulo ax is result
    sub cx, dx
    xor al, al
    mov ah, 0x0F
    newline_loop:
        movzx bx, byte [cursor]
        mov di, bx
        stosw
        add byte [cursor], 2
        sub cx, 2
        cmp cx, 0
        jg newline_loop

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
; ES need to be set to 0xb800 
cprint:   
    mov ah, 0x0F   ; attrib = black on white
    mov cx, ax    ; save char/attribute
    movzx ax, byte [cursor]
    mov di, ax      ; set offset
    
    mov ax, cx        ; restore char/attribute
    stosw              ; write char/attribute
    add byte [cursor], 2  ; advance to right
    
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

clearscreen:
    mov ax, 0xb800 
    mov es, ax 
    mov al, '_'   ; char
    mov ah, 0x0F ; attr
    
    xor cx, cx
    clearscreen_loop:
        xor di, di
        add di, cx
        stosw
        add cx, 2
        cmp cx, VIDEO_MEM_SZ
        jle clearscreen_loop
    ret
;-----------------------------------------------

VIDEO_MEM_SZ equ 3999
SCREEN_WIDTH equ 160

cursor db 0
xpos   db 0
ypos   db 0
hexstr   db '0123456789ABCDEF'
outstr16   db '0000', 0  ;register value string
reg16   dw    0  ; pass values to printreg16