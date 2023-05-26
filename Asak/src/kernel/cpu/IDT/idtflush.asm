global idt_flush          ; Allows the C code to link to this
idt_flush:
    mov eax, [esp+4]        ; Get the pointer to the IDT, passed inside as a parameter
    lidt [eax]              ; Load the IDT pointer
    ret