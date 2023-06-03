[GLOBAL idt_load] ; allows c code to call idt_load
extern idtp

idt_load:
    lidt [idtp]
    ret