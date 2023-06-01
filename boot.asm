    jmp main

%include "lib/io.asm"
main:
[ORG 0x7c00]      ; add to offsets
   xor ax, ax    ; make it zero
   mov ds, ax   ; DS=0
   mov ss, ax   ; stack starts at 0
   mov sp, 0x9c00   ; 2000h past code start
 
   cld
 
   mov ax, 0xb800   ; text video memory
   mov es, ax
 
   mov si, msg   ; show text string
   call sprint
 
   mov ax, 0xb800   ; look at video mem
   mov gs, ax
   mov bx, 0x0000   ; 'W'=57 attrib=0F
   mov ax, [gs:bx]
 
   mov  word [reg16], ax ;look at register
   call printreg16
 
hang:
   jmp hang

xpos   db 0
ypos   db 0
hexstr   db '0123456789ABCDEF'
outstr16   db '0000', 0  ;register value string
reg16   dw    0  ; pass values to printreg16
msg   db "What are you doing, Dave?", 0
times 510-($-$$) db 0
db 0x55
db 0xAA