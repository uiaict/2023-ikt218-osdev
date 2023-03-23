; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
global gdt_flush            ; Allows the C code to link to this
gdt_flush:
    mov eax, [esp+4]        ; Get the pointer to the GDT, passed as a parameter.
    lgdt [eax]              ; Load the new GDT pointer
    jmp 0x08:complete_flush ; Far jump to complete_flush

complete_flush:
    mov ax, 0x10
    mov ds, ax              ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret                     ; Returns back to the C code!