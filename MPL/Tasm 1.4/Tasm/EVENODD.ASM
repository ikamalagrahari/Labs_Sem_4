.model small
.stack 100h

.data
    number DB ?
    msg_even DB "The number is even", 13, 10, "$"
    msg_odd DB "The number is odd", 13, 10, "$"

.code
    mov ax, @data
    mov ds, ax

    mov ah, 01h
    int 21h
    sub al, 30h
    mov number, al

    mov ah, 0

    mov al, number
    and al, 00000001b

    jz even
    jmp odd

even:
    mov ah, 09h
    lea dx, msg_even
    int 21h
    jmp exit_prog

odd:
    mov ah, 09h
    lea dx, msg_odd
    int 21h

exit_prog:
    mov ah, 4Ch
    int 21h

end

