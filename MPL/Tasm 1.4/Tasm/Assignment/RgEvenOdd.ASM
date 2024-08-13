.model small
.stack 100h

.data
    number DB ?
    result DB ?

.code
main:
    mov ax, @data
    mov ds, ax
    
    mov si, 1000h
    mov al, [si]
    test al, 01h
    jnz odd_number
    mov result, 00h
    jmp end_program
odd_number:
    mov result, 01h
end_program:
    mov di, 1001h
    mov al, result
    mov [di], al

    mov ah, 4Ch
    int 21h

end main


