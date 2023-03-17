; Source: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

; Implement a global discriptor table in assembly

; db = double bytes
; dw = word
; dd = double word

gdt_start:

; GDT start
gdt_null: ; null descriptor
    ; Starts with a null 8-byte
    dd 0x0 ; dd defines a double word (4 bytes)
    dd 0x0

; code segment
gdt_code:
    dw 0xffff ; Limit -> Defines the segment size

    ; First 24 bits of the base
    dw 0x0 ; segment base first 16 bits (0-15)
    db 0x0 ; segment base last 8 bits (16-23)

    ; Flags
    db 10011010b ; = present, privilege, type
    db 11001111b ; = other flags and size limit

    ; Last base bits
    db 0x0 ; segment base last 8 bits (24-31) 

; data segment
gdt_data:
    dw 0xffff ; Limit -> Defines the segment size

    ; First 24 bits of the base
    dw 0x0 ; segment base first 16 bits (0-15)
    db 0x0 ; segment base last 8 bits (16-23)

    ; Flags
    db 10010010b ; code bit set to 0 (bit nr 5, if starting from 1)
    db 11001111b ; = other flags and size limit

    ; Last base bits
    db 0x0 ; segment base last 8 bits (24-31) 

gtd_end: ; Label to help the assembler calculate GDT size

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of GDT
    dd gdt_start ; GDT start address

; Constants for segment memory location
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start