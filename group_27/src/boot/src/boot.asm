; Set constants for the multiboot header
MBALIGN equ 1<<0                ; 
MEMINFO equ 1<<1                ;
FLAGS equ MBALIGN | MEMINFO     ; 
MAGIC equ 0x1BADB002            ; Assigning multiboot magic header
CHECKSUM equ -(MAGIC + FLAGS)   ; Create a checksum to make sure that the MAGIC and flags are correct

; Multiboot header
section .multiboot              ; Create section       
align 4                         
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Specify the block starting symbol
; BSS contains statically allocated variables that are declared but have not been assigned a value yet
; https://en.wikipedia.org/wiki/.bss
section .bss
align 16
    stack_bottom:
    resb 16384          ; 16 KiB
    stack_top:

; Specify the code section
section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top   
    extern init_gdt
    call init_gdt                               ; Set the stack pointer
    extern init_idt
    call init_idt
    extern kernel_main                          ; Set the kernel_main entry point
    call kernel_main                            ; Call the kernel_main function
    cli                                         ;
.hang:
    hlt
    jmp .hang
.end: