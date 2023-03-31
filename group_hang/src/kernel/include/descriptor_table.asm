gdtr DW 0 ; For limit storage
     DD 0 ; For base storage
 
setGdt:
   XOR   EAX, EAX
   MOV   AX, DS
   SHL   EAX, 4
   ADD   EAX, ''GDT''
   MOV   [gdtr + 2], eax
   MOV   EAX, ''GDT_end''
   SUB   EAX, ''GDT''
   MOV   [gdtr], AX
   LGDT  [gdtr]
   RET