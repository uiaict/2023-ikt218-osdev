bits 32

; Configuration of Multiboot flags
MBOOT_PAGE_ALIGN       equ 1<<0    ; Multiboot flag: Load kernel and modules on a page boundary
MBOOT_MEM_INFO         equ 1<<1    ; Multiboot flag: Provide your kernel with memory info

; Definition of Multiboot header values
MBOOT_AOUT_KLUDGE      equ 0x00010000;
MBOOT_HEADER_MAGIC     equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS     equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO ; Configure flags for Multiboot
MBOOT_CHECKSUM         equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS) ; Checksum for Multiboot header

; Stack configuration. The size of our stack (16KB).
STACK_SIZE equ 0x4000

; Multiboot section
section .multiboot
multiboot:
align 4
    dd  MBOOT_HEADER_MAGIC      ; Required for GRUB to recognize the file as Multiboot
    dd  MBOOT_HEADER_FLAGS      ; Multiboot flags
    dd  MBOOT_CHECKSUM          ; Ensure correct Multiboot header values

		; Reserved fields
		dd 0
		dd 0
		dd 0 
		dd 0 
		dd 0 

    ; Graphics mode
    dd 0
    dd 640
    dd 480
    dd 32

; Define the stack
section .bss
align 16
stack_bottom:
    resb STACK_SIZE ; Reserve bytes for stack
top_of_stack:

; Entry point of our program
section .text
global _start:function (_start.end - _start)
_start:
	; Set the stack pointer
	mov esp, top_of_stack

	; Call the functions to initialize GDT and IDT
	extern initialize_gdt
	call initialize_gdt
	extern initialize_idt
	call initialize_idt

	; Call the main function of the kernel
	extern main_kernel
	call main_kernel

	; Disable interrupts
	cli
    
.hang:	
	; Enter an infinite loop
	hlt
	jmp .hang
.end:
