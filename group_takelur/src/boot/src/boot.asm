; Code inspired from https://wiki.osdev.org/Bare_Bones
; Modified to NASM assembly

; Constants for the multiboot header 
MULTIBOOT_PAGE_ALIGN equ 1<<0                                   ; Load the kernel and modules at a page boundary
MULTIBOOT_MEM_INFO equ 1<<1                                     ; Send memory information to the kernel
MULTIBOOT_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO   ; Flags for the multiboot header
MULTIBOOT_MAGIC equ 0x1BADB002                                  ; Magic number for the multiboot header
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)     ; Checksum for the multiboot header

; Declares the multiboot header to mark the program as a kernel. The bootloader searches for the magic number 
; in the first 8KiB of the kernel file, aligned at a 32-bit boundary - https://wiki.osdev.org/Bare_Bones.
[BITS 32]                               ; Tells assembler to generate instructions for the 32-bit processor mode
SECTION .multiboot
    align 4                             ; Align to 4 byte (32 bit) boundary
multiboot:                              ; Label = multiboot
    dd MULTIBOOT_MAGIC                  ; Start with the magic number (dd = define double word = 32 bits)
    dd MULTIBOOT_FLAGS                  ; Then the flags
    dd MULTIBOOT_CHECKSUM               ; Then the checksum

; I have to provide the stack in kernel as there is no stack value definition in the multiboot standard.
SECTION .bss
    align 16                            ; Align to 16 byte (128 bit) boundary (required on x86)
stack_bottom: 
    resb 16384                          ; Reserve 16 KiB for the stack
stack_top:                              ; Stack_top is the end of the stack. The stack grows downwards.

