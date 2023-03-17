; Enter 32-bit protected mode

[bits 16] ; Tells assembler to encode instructions as 16-bit
cli ; disable interrupts

lgdt [gdt_descriptor] ; Load GDT

; Switch to protected mode
mov eax, cr0 ; Moved control register 0 to eax register
or eax, 0x1 ; Changes last bit of eax to 1
mov cr0, eax ; Move new eax value to the control register

; Sets a far jump by explicitly setting
; the target segment.
jmp CODE_SEG:start_protected_mode

[bits 32] ; Tells assembler to encode instructions as 32-bit
start_protected_mode: ; Successfully switched to protected mode

    ; Point segment registers to data selector

    mov ax, DATA_SEG ; Moves the data segment to the ax register
    mov ds, ax ; Moves ax value (DATA_SEG) to data segment register
    mov ss, ax ; Moves DATA_SEG into stack segment register, which sets the starting address of the stack

    ; Moves DATA_SEG into extra segment registers
    mov es, ax 
    mov fs, ax 
    mov gs, ax 

    mov ebp, 0x90000
    mov esp, ebp ; Updates stack pointer to the top of the free space

    call BEGIN_PM
