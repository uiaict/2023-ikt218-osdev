; Code inspired from https://wiki.osdev.org/Bare_Bones
; Modified to NASM assembly

; Constants for the multiboot header 
MULTIBOOT_PAGE_ALIGN equ 1<<0                                   ; Load the kernel and modules at a page boundary
MULTIBOOT_MEM_INFO equ 1<<1                                     ; Send memory information to the kernel
MULTIBOOT_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO   ; Flags for the multiboot header
MULTIBOOT_MAGIC equ 0x1BADB002                                  ; Magic number for the multiboot header
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)     ; Checksum for the multiboot header

