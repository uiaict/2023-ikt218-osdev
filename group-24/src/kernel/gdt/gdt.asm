; Function: gdt_flush
; Description: Flushes the Global Descriptor Table (GDT) by loading a new GDT descriptor, setting segment registers, and performing a jump to the updated code segment.
; Input: None
; Output: None

global gdt_flush

section .text

gdt_flush:
    lgdt [esp + 4]
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax
    jmp 0x08:.flush

.flush:
    ret
