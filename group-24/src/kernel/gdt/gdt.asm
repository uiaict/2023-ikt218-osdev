; Function: gdt_flush
; Description: Flushes the Global Descriptor Table (GDT) by loading a new GDT descriptor, 
; setting segment registers, and performing a jump to the updated code segment.
; Input: None
; Output: None

global gdt_flush



gdt_flush:
    mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
    lgdt [eax]        ; Load the new GDT pointer

    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax        ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    ret

flush:
    ret
