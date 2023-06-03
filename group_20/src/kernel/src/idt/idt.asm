global idt_flush    ; Allows main code to call idt_flush

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
    lidt [eax]        ; Loads the IDT pointer.
    ret


; SOURCES: https://github.com/uiaict/ikt218-osdev/pull/1