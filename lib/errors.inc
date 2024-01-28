; 1 - error code        
; 2 - called method
; 3 - cmp arg0
; 4 - cmp arg1
; 5 - conditional jump
%macro err_call 5
mov word [err_cd], %1
call %2
cmp %3, %4
%5 err
%endmacro


; Call error by value in BX
err_hndl:
    mov si, msg_err
    call sprint
    
    push bx
    mov word [reg16], bx
    call printreg16
    pop bx

    call get_err_indx
    cmp bx, err_list_sz
    jge err0 ; uknown error
    jmp [err_list + bx]
    err_hndl__exit:
        call sprint
        ret

; Find offset of err_list index
; Input is in BX and so is ouput
; Affects AX, CX
get_err_indx:
    mov ax, bx
    mov cx, 2
    mul cx
    mov bx, ax
    ret

msg_err0 db "General error", 10, 0
; General error - default error
err0:
    mov si, msg_err0
    jmp err_hndl__exit
msg_err1 db "A20 is not enabled", 10, 0
; A20 is disabled
err1:
    mov si, msg_err1
    jmp err_hndl__exit
msg_err2 db "Cool error", 10, 0
err2:
    mov si, msg_err2
    jmp err_hndl__exit

msg_err db "ERROR: #", 0
err_list dw err0, err1
err_list_sz equ $ - err_list 