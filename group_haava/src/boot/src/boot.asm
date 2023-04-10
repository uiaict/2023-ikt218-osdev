MBOOT_PAGE_ALIGN       equ 0x00000001 ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO         equ 0x00000002 ; Provide kernel with memory info
MBOOT_HEADER_MAGIC     equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS     equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM         equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; Stack configuration. The size of our stack (16KB).
KERNEL_STACK_SIZE equ 0x4000

section .multiboot
multiboot:
align 4
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_CHECKSUM

section .bss
align 16
stack_bottom:
resb KERNEL_STACK_SIZE
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top

    extern kernel_main
    call kernel_main

    cli
.hang: hlt
    jmp .hang
.end:
