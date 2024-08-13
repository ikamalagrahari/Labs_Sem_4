.model small
.stack 100h

.data
    input_str DB 100 DUP('$')
    output_str DB 100 DUP('$')

.code
main:
    mov ax, @data
    mov ds, ax
    
    mov ah, 0Ah
    lea dx, input_str
    int 21h
    
    lea si, input_str+1
    lea di, output_str+1 
reverse_loop:
    mov cx, 0
next_char:
    mov al, [si]
    cmp al, ' '
    je space_found
    inc si
    inc cx
    test al, al
    jnz next_char
    jmp end_reverse
space_found:
    mov si, si
    dec si
    mov bx, cx
print_word:
    mov al, [si]
    mov [di], al
    inc di
    dec si
    loop print_word
    mov byte ptr [di], ' '
    inc di
    jmp reverse_loop
end_reverse:
    mov byte ptr [di-1], '$'
    mov dx, offset output_str
    mov ah, 09h
    int 21h

    mov ah, 4Ch
    int 21h

end main


