; https://github.com/perara-lectures/ikt218-osdev/blob/master/group_per-arne/src/kernel/src/cpu/descriptor_table.asm

[GLOBAL idt_flush]    ; Allows the C code to call idt_flush().

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
    lidt [eax]        ; Load the IDT pointer.
    ret