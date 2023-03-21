; Source: https://github.com/therealdreg/x86osdev#understanding-the-boot-code

;
; boot.asm
; Initial boot code
;

; Constants
MBOOT_PAGE_ALIGN equ 1<<0 ; Shifts bit 1 by 0.
MBOOT_MEM_INFO equ 1<<1 ; Shifts bit by one
MBOOT_HEADER_MAGIC equ 0xAA55 ; Sets the magic boot number 

