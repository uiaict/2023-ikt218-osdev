; Function: gdt_flush
; Description: Flushes the Global Descriptor Table (GDT) by loading a new GDT descriptor, setting segment registers, and performing a jump to the updated code segment.
; Input: None
; Output: None
gdt_flush:
    mov eax, [esp+4]   ; Get the address of the new GDT descriptor from the stack
    lgdt [eax]         ; Load the new GDT descriptor using the LGDT instruction
    mov ax, 0x10       ; Set up the data segment registers (DS, ES, FS, GS, SS) to use the new GDT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush    ; Perform a jump to the updated code segment
.flush:
    ret                ; Return from the function
