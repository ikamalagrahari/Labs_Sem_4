DATA SEGMENT
    numbers DB 10, 3, 6, 1, 9, 2, 8, 7, 5, 4
    num_count DB 10
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    
START:
    MOV AX, @DATA
    MOV DS, AX
    
    MOV CX, num_count
OuterLoop:
    MOV SI, 0
InnerLoop:
    MOV DI, SI
    INC DI
    MOV AL, numbers[SI]
    CMP AL, numbers[DI]
    JBE NotSwap       
    MOV BL, numbers[SI]
    MOV numbers[SI], numbers[DI]
    MOV numbers[DI], BL
NotSwap:
    INC SI
    LOOP InnerLoop
    DEC CX
    JNZ OuterLoop

    MOV CX, num_count
    MOV SI, 0
DisplayLoop:
    MOV DL, numbers[SI]
    ADD DL, 30h
    MOV AH, 02h
    INT 21h
    INC SI
    LOOP DisplayLoop

    MOV AH, 4Ch
    INT 21h

CODE ENDS
END START


