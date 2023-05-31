bits 32

MBOOT_PAGE_ALIGN       equ 1<<0    
MBOOT_MEM_INFO         equ 1<<1    
MBOOT_AOUT_KLUDGE      equ 0x00010000
MBOOT_HEADER_MAGIC     equ 0x1BADB002 
MBOOT_HEADER_FLAGS     equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO ;| MBOOT_VIDEO_MODE_BIT
MBOOT_CHECKSUM         equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; Stack configuration. The size of our stack (16KB).
KERNEL_STACK_SIZE equ 0x4000

section .multiboot
multiboot:
align 4
    dd  MBOOT_HEADER_MAGIC     
    dd  MBOOT_HEADER_FLAGS      
    dd  MBOOT_CHECKSUM         

		dd 0
		dd 0
		dd 0 
		dd 0 
		dd 0 
    ; Graphic field
    dd 0
    dd 640
    dd 480
    dd 32

section .bss
align 16
stack_bottom:
resb KERNEL_STACK_SIZE 
stack_top:

section .text
global _start:function (_start.end - _start)
_start:

  mov esp, stack_top    ; this moved the system from real mode to protected mode

  ; call the cpp function init kernel memory through the function init kernel
 extern init_kernel     
 call init_kernel


  ; call the cpp function init GDT wich initialize the global deskriptor table
  extern init_gdt
	call init_gdt
   
  

     ; call the cpp function init IDT wich initialize the interrupt deskriptor table
    extern init_idt
    call init_idt

   ; call the cpp function init IDT wich initialize the interrupt servise rutines
    extern init_isr
    call init_isr

  ; call the kernel_main function
	extern kernel_main
	call kernel_main  

	
	cli
  ; start an endless loop
.hang:	hlt
	jmp .hang
.end: