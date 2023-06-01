[ORG 0x7c00]      ; add to offsets
    jmp main
    
    %include "lib/print.inc"

main:
    xor ax, ax    ; make it zero
    mov ds, ax   ; DS=0
    mov ss, ax   ; stack starts at 0
    mov sp, 0x9c00   ; 2000h past code start
    
    cld

    call clear

    mov ax, 0xb800   ; text video memory
    mov es, ax

    mov si, msg   ; show text string
    call sprint
    
    mov ax, 0xb800   ; look at video mem
    mov gs, ax
    mov bx, 0x0000   ; 'H'=48 attrib=0F
    mov ax, [gs:bx]

    mov word [reg16], ax
    call printreg16
 
hang:
    jmp hang

xpos   db 0
ypos   db 0
msg   db "Hello", 10, " world", 10, 0
times 510-($-$$) db 0
db 0x55
db 0xAA