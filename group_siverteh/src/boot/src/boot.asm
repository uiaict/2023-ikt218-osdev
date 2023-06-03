;Code taken from https://wiki.osdev.org/Bare_Bones
;Not my own code, as it is the basic code needed to boot the system

;Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)   ; checksum of above, to prove we are multiboot
 

[BITS 32]

;Declares the multiboot header with the constants set above.
section .multiboot
align 4
multiboot:
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

	;MULTIBOOT_AOUT_KLUDGE
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0

	;MULTIBOOT_VIDEO_MODE
	dd 0
	dd 640
	dd 480
	dd 32

; The .bss section is used to declare uninitialized data, in this case a stack of size 16 KiB.
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:
 
; The .text section is used to declare code 
section .text
global _start:function (_start.end - _start)
_start:
	;Calls the initialize_multiboot function found in boot.cpp.
	extern initialize_multiboot
	push ebx
	push eax
	call initialize_multiboot	

	;Sets the stack pointer to the address of the address of the stack_top.
	mov esp, stack_top

	; Calls the kernel_main function found in main.cpp.
	extern kernel_main
	call kernel_main


;Clears interrupts, and enters an infinite loop.
	cli
.hang:	hlt
	jmp .hang
.end: