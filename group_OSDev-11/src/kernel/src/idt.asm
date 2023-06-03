[GLOBAL flush_idt]    ; Global label to allow the C code to call flush_idt().

flush_idt:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
    lidt [eax]        ; Load the IDT pointer.
    ret               ; Return from the function.