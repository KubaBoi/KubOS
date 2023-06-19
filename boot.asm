[ORG 0x7c00]      ; add to offsets
   jmp start
 
   %include "lib/print.inc"
   ;%include "lib/key_handler.inc"
   ;%include "lib/a20.inc"
   ;%include "lib/errors.inc"
 
start:   
    xor ax, ax   ; make it zero
    mov ds, ax   ; DS=0
    mov ss, ax   ; stack starts at 0
    mov sp, 0x9c00   ; 200h past code start

    push ds      ; save real mode
 
    lgdt [gdtinfo]   ; load gdt register
    
    mov  eax, cr0   ; switch to pmode by
    or al,1         ; set pmode bit
    mov  cr0, eax
    
    mov  bx, 0x08   ; select descriptor 1
    mov  ds, bx   ; 8h = 1000b
    
    and al,0xFE     ; back to realmode
    mov  cr0, eax   ; by toggling bit again
    
    pop ds      ; get back old segment
    sti
    
    mov bx, 0x0f01   ; attrib/char of smiley
    mov eax, 0x0b8000 ; note 32 bit offset
    mov word [ds:eax], bx
    
    mov ax, 0xb800   ; text video memory
    mov es, ax
    call clearscreen
    
    mov si, msg
    call sprint
    
    ;err_call 1, check_a20, ax, 1, je

    ;call init_keyhndl
    
    jmp $      ; loop forever
 
;err:
    ;mov bx, word [err_cd]
    ;call err_hndl

; lowest byte of Limit
; highest byte of Limit
; lowest byte of Base Addr
; next byte of Base Addr
; third byte of Base Addr
; 0 - 00 - 0 - 0000 = P - DPL - S - Type 
; 0 - 0 - 0 - 0 - 0000 = G - D/B - R - AVL - Size 
; fourth byte of Base Addr
gdtinfo:
   dw gdt_end - gdt - 1   ;last byte in table
   dd gdt         ;start of table
 
gdt        dd 0,0  ; entry 0 is always unused
flatdesc    db 0xff, 0xff, 0, 0, 0, 10010010b, 11001111b, 0
gdt_end:

err_cd dw 0
port60   dw 0 
msg   db "KubOS", 10, "=====", 10, 0
times 510-($-$$) db 0  
dw 0xAA55  