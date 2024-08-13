DATA SEGMENT
    NO DB 49H
    Z DB ?
    O DB ?
DATA ENDS
 
CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX
    MOV AL, NO
    MOV BL, 00H
    MOV CX, 08H
    MOV DL, 00H
 
UP:
    ROL AL, 1
    JC ONE
    INC BL
    JMP NXT
 
ONE:
    INC DL
 
NXT:
    DEC CX
    JNZ UP
  
    MOV Z, BL ; Store the count of '1's in Z
    MOV O, DL ; Store the count of '0's in O
  
    INT 3
CODE ENDS
END START



