;
; boot.s -- Kernel start location. Also defines multiboot header.
;
bits 32


MBOOT_PAGE_ALIGN       equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO         equ 1<<1    ; Provide your kernel with memory info
;MBOOT_VIDEO_MODE_BIT   equ 1<<2    ; Must pass video information to OS.
MBOOT_AOUT_KLUDGE      equ 0x00010000;
MBOOT_HEADER_MAGIC     equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS     equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO ;| MBOOT_VIDEO_MODE_BIT
MBOOT_CHECKSUM         equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; Stack configuration
; The size of our stack (16KB).
KERNEL_STACK_SIZE equ 0x4000

; AOUT Kludge
AOUT_KLUDGE equ MBOOT_AOUT_KLUDGE

; Declare a multiboot header that marks the program as a kernel. These are magic
; values that are documented in the multiboot standard. The bootloader will
; search for this signature in the first 8 KiB of the kernel file, aligned at a
; 32-bit boundary. The signature is in its own section so the header can be
; forced to be within the first 8 KiB of the kernel file.

section .multiboot
multiboot:
align 4
    dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
    dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
    dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct



    ; Address field (this fields are required in a.out format)
    dd $0
    dd $0
    dd $0
    dd $0
    dd $0

    ; Graphic field
    dd 0
    dd 640
    dd 480
    dd 32

; The multiboot standard does not define the value of the stack pointer register
; (esp) and it is up to the kernel to provide a stack. This allocates room for a
; small stack by creating a symbol at the bottom of it, then allocating 16384
; bytes for it, and finally creating a symbol at the top. The stack grows
; downwards on x86. The stack is in its own section so it can be marked nobits,
; which means the kernel file is smaller because it does not contain an
; uninitialized stack. The stack on x86 must be 16-byte aligned according to the
; System V ABI standard and de-facto extensions. The compiler will assume the
; stack is properly aligned and failure to align the stack will result in
; undefined behavior.
section .bss
align 16
stack_bottom:
resb KERNEL_STACK_SIZE ; 16 KiB
stack_top:




; The linker script specifies _start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesn't make sense to return from this function as the bootloader is gone.
; Declare _start as a function symbol with the given symbol size.
section .text
global _start:function (_start.end - _start)
_start:
	
	extern init_multiboot
	push ebx						; Pass a pointer to the multiboot header, filled in by the bootloader
	call init_multiboot


	
	mov esp, stack_top

	
    ;extern init_constructors
    ;call init_constructors
    ;extern init_gdt
    ;call init_gdt
    
    mov eax, 1 
    mov ebx, 0
   
    ; Initialize the Interrupt Descriptor Table
    ;extern init_idt
    ;call init_idt

    ; Initialize the Interrupt Service Routine
    ;extern init_isr
    ;call init_isr

	
	extern kernel_main
	call kernel_main  ; call our kernel_main() function.

	
	cli
.hang:	hlt
	jmp .hang
.end:



