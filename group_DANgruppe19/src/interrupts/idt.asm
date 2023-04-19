; idt.asm

global idt_set_gate
global idt_install

extern idt_ptr

section .text

idt_set_gate:
    ; Save registers
    pusha

    ; Set up the IDT entry
    mov word [eax + 0], cx ; base_low
    mov word [eax + 2], dx ; selector
    mov byte [eax + 4], 0  ; always0
    mov byte [eax + 5], bl ; flags
    mov word [eax + 6], si ; base_high

    ; Restore registers
    popa
    ret

idt_install:
    ; Load the IDT using the lidt instruction
    lidt [idt_ptr]

    ; Enable interrupts (Clear IF flag)
    sti
    ret
