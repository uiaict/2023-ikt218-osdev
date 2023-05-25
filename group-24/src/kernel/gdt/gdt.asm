; Function: gdt_flush
; Description: Flushes the Global Descriptor Table (GDT) by loading a new GDT descriptor, 
; setting segment registers, and performing a jump to the updated code segment.
; Input: None
; Output: None

global gdt_flush

extern gp

gdt_flush:
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush

flush:
    ret
