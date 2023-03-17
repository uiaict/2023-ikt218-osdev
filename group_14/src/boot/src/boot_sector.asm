; Boot sector to enter 32-bit mode

[org 0x7c00] ; Sets location counter

mov bp, 0x9000 ; Set base pointer position. Sets up stack
mov sp, bp ; Set stack pointer to the value of base pointer

mov bx, MSG_REAL_MODE ; Move real mode message to bx register
call print_string

%include "gdt.asm"
%include "enter_32bit_pm.asm"
%include "../print/print_string.asm"
%include "print_string.asm"

call enter_32bit_pm ; Enter 32-bit mode. Returns BEGIN_PM

; Begin protected mode
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    jmp $ ; Infinite loop


times 510-($-$$) db 0 
dw 0xaa55 ; Magic number