; Derived from https://wiki.osdev.org/Bare_Bones_with_NASM
; Set constants for the multiboot header
MBALIGN equ 1<<0                ; Sets MBALIGN to 1
MEMINFO equ 1<<1                ; Sets MEMINFO to 2
FLAGS equ MBALIGN | MEMINFO     ; Set these two as flags
MAGIC equ 0x1BADB002            ; Assigning multiboot magic header
CHECKSUM equ -(MAGIC + FLAGS)   ; Create a checksum to make sure that the MAGIC and flags are correct

; Multiboot header
section .multiboot              ; Create multiboot section       
align 4                         ;
    dd MAGIC                    ; Set MAGIC header so GRUB will know this is multiboot
    dd FLAGS                    ; Sets the flags
    dd CHECKSUM                 ; Create checksum to make sure the flags are set correctly

; Specify the block starting symbol
; BSS contains statically allocated variables that are declared but have not been assigned a value yet
; https://en.wikipedia.org/wiki/.bss
section .bss
align 16
    stack_bottom:               ; Assigns the bottom of the stack
    resb 16384                  ; 16 KiB
    stack_top:                  ; Sets the top of the stack. The stack grows downwards

; Specify the code section
section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top          ;
    extern init_gdt             ; Set the initi_gdt entry point
    call init_gdt                       ; Set up the GDT
    extern init_idt
    call init_idt
    extern kernel_main          ; Set the kernel_main entry point
    call kernel_main            ; Call the kernel_main function
    cli                         ; Disable interrupts (CLear Interrupt bit)
.hang:                          ; Set keyword "hang" as function hlt (halt)
    hlt
    jmp .hang                   ; Run hang (loop intializer)
.end:                           ; End of assembly program