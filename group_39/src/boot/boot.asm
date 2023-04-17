; Written by IKT 218 Group 39 spring 2023

; This file defines a Multiboot-compliant kernel entry point that can be loaded by GRUB.

bits 32 ; Declares that the assembler should generate 32-bit code. This is an assembler directive.


MULTIBOOT_MAGIC     equ 0x1BADB002  ; Magic number that the bootloader will be looking for, according to the multiboot specification.
MULTIBOOT_FLAGS     equ 0x0  ;   Flags, currently not using this.
MULTIBOOT_CHECKSUM  equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)   ; Checksum. Negated sum of magic number + flags, as sum of checksum + magic number and flags needs to equal 0.



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


;; Code segment
section .text
global _start:
extern kernel_main
extern init_gdt

_start:
    cli
    call init_gdt