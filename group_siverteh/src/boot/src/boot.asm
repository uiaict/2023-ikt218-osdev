; Code taken from https://wiki.osdev.org/Bare_Bones
; Not my own code, as it is the basic code needed to boot the system

; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)   ; checksum of above, to prove we are multiboot
 
; Declare a multiboot header that marks the program as a kernel. These are magic
; values that are documented in the multiboot standard. The bootloader will
; search for this signature in the first 8 KiB of the kernel file, aligned at a
; 32-bit boundary. The signature is in its own section so the header can be
; forced to be within the first 8 KiB of the kernel file.
[BITS 32]
section .multiboot
align 4
multiboot:
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

	; MULTIBOOT_AOUT_KLUDGE
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0

	; MULTIBOOT_VIDEO_MODE
	dd 0
	dd 640
	dd 480
	dd 32
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:
 
section .text
global _start:function (_start.end - _start)
_start:
	extern initialize_multiboot
	push ebx
	push eax
	call initialize_multiboot	

	mov esp, stack_top

	extern kernel_main
	call kernel_main


	cli
.hang:	hlt
	jmp .hang
.end: