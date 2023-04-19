; isr.asm

global isr0
global isr1
global isr2

extern divide_by_zero_handler
extern non_maskable_interrupt_handler
extern debug_handler

section .text

isr0:
    cli
    pusha
    call divide_by_zero_handler
    popa
    sti
    iret

isr1:
    cli
    pusha
    call non_maskable_interrupt_handler
    popa
    sti
    iret

isr2:
    cli
    pusha
    call debug_handler
    popa
    sti
    iret
