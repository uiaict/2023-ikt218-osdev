
bits 32

; Configuration of Multiboot flags
PAGE_ALIGNMENT_FLAG    equ 1<<0    ; Load kernel and modules on a page boundary
MEMORY_INFO_FLAG       equ 1<<1    ; Provide your kernel with memory info

; Definition of Multiboot header values
MBOOT_MAGIC            equ 0x1BADB002 ; Multiboot Magic value
MBOOT_FLAGS            equ PAGE_ALIGNMENT_FLAG | MEMORY_INFO_FLAG
MBOOT_CHECKSUM         equ -(MBOOT_MAGIC + MBOOT_FLAGS)

; Definition of stack configuration (16KB)
STACK_SIZE              equ 0x4000

; Section for Multiboot header information
section .multiboot
multiboot:
    align 4
    dd MBOOT_MAGIC       ; Magic number to identify the Multiboot header
    dd MBOOT_FLAGS       ; Flags indicating the kernel features supported by the bootloader
    dd MBOOT_CHECKSUM    ; Checksum of the Multiboot header

    times 5 dd 0         ; Reserved fields

    ; Graphic field
    dd 0                 ; Address of framebuffer
    dd 640               ; Width of screen
    dd 480               ; Height of screen
    dd 32                ; Bits per pixel

; Section for uninitialized data (BSS)
section .bss
    align 16
stack_base:
    resb STACK_SIZE      ; Reserve memory for the stackz
stack_end:

; Section for executable code
section .text
    global _start:function (_start.finish - _start)

    ; Entry point of kernel
    _start:
        mov esp, stack_end ; Set the stack pointer to the top of the stack
        ; initialize GDT
	    extern gdt_init
	    call gdt_init 

        ; initialize IDT
	    extern idt_init
	    call idt_init
        
        extern main_kernel ; Declare the kernel_main function
        call main_kernel   ; Call the kernel_main function
        cli                ; Disable interrupts

    ; Loop to halt processor execution
    .loop:
        hlt                ; Halt the processor until the next interrupt
        jmp .loop          ; Jump to the beginning of the loop

    ; End of kernel execution
    .finish:
    