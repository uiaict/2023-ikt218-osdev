; Written by IKT 218 Group 39 spring 2023

; This file defines a Multiboot-compliant kernel entry point that can be loaded by GRUB.

bits 32 ; Declares that the assembler should generate 32-bit code. This is an assembler directive.


MULTIBOOT_MAGIC     equ 0x1BADB002  ; Magic number that the bootloader will be looking for, according to the multiboot specification.
MULTIBOOT_FLAGS     equ 0x0  ;   Flags, currently not using this.
MULTIBOOT_CHECKSUM  equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)   ; Checksum. Negated sum of magic number + flags, as sum of checksum + magic number and flags needs to equal 0.

KERNEL_STACK_SIZE equ 0x4000 ; Defines the size of our stack, 16KB. We will use this definition further down in the assembly code.



; This defines the multiboot header to be located by the bootloader, GRUB.
align 4
section .multiboot

    ;; The following entries are 'linker scripts'.
    ;; 'dd' means 'define doubleword', and is not an x86 instruction.
    ;; Instead, it is an assembler directive to define a 32-bit value. 
    ;; Can be compared to how a preprocessor in languages such as C and C++ works.
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

; Here we set up and provide a stack for our kernel.
section .bss
align 16 ; Align to 16 bytes.
stack_bottom:
resb KERNEL_STACK_SIZE ; Reserve space for our stack, in this case 16KB. 
stack_top:


section .text
global _start:
extern kernel_main
extern init_gdt
extern init_idt

_start:
    mov esp, stack_top ; Set the esp register to point to top of the stack. 
    cli ; Disable interrupts
    call init_gdt ; Call init_gdt which sets up and loads the GDT into memory.
    call init_idt ; Call init_idt to set up and load IDT (Interrupt Descriptor Table).
    sti; Enable interrupts
    call kernel_main ; Call the main function of the kernel.


.hang:	hlt
	jmp .hang ; This makes an infinite loop. But because interrupts are disabled, the CPU will basically stop and do nothing.
.end:
