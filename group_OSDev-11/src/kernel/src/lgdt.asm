[GLOBAL flush_gdt]    ; Mark flush_gdt as a function callable from our C code.

flush_gdt:
    mov eax, [esp+4]  ; Retrieve the pointer to the GDT provided as an argument.
    lgdt [eax]        ; Set the new GDT pointer.

    mov ax, 0x10      ; 0x10 is the position of our data segment in the GDT.
    mov ds, ax        ; Assign all segment selectors to use our data segment.
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; Perform a far jump to our code segment located at GDT offset 0x08!

.flush:
    ret               ; Return from the flush_gdt function.