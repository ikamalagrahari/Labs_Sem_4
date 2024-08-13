data segment
    a dw 1234H
    b dw 0100H
data ends

code segment
assume cs:code, ds:data
start:
    mov     ax, data
    mov     ds, ax
    mov     ax, a
    mov     bx, b
    add     al, bl
    daa
    mov     bl, al
    adc     ah, bh
    mov     al, ah
    daa
    mov     bh, al
    mov     ch, 04h
    mov     cl, 04h
l2:
    rol     bx, cl
    mov     dl, bl
    and     dl, 0FH
    cmp     dl, 09h
    jbe     l4 
    add     dl, 07h
l4:
    add     dl, 30h
    mov     ah, 02h
    int     21h
    dec     ch
    jnz     l2 
    mov     ah, 4ch
    int     03h

code ends
end start
