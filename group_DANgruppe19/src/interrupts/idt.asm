; idt.asm

global idt_set_gate
global idt_install

extern idt_ptr

section .text

idt_set_gate:
    ; Save registers
    pusha

    ; Combine the base address into edx
    mov edx, ecx
    shl edx, 16
    or edx, ebx

    ; Set up the IDT entry
    mov word [eax + 0], dx ; base_low
    mov word [eax + 2], si ; selector
    mov byte [eax + 4], 0  ; always0
    mov byte [eax + 5], cl ; flags
    shr edx, 16
    mov word [eax + 6], dx ; base_high

    ; Restore registers
    popa
    ret
    
idt_install:
    ; Load the IDT using the lidt instruction
    lidt [idt_ptr]

    ; Enable interrupts (Clear IF flag)
    sti
    ret
