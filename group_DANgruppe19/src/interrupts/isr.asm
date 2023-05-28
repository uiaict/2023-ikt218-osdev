; isr.asm

global isr0
global isr1
global isr2

extern divide_by_zero_handler
extern non_maskable_interrupt_handler
extern debug_handler

section .text

isr0:
    pusha
    call divide_by_zero_handler
    popa
    iret

isr1:
    pusha
    call non_maskable_interrupt_handler
    popa
    iret

isr2:
    pusha
    call debug_handler
    popa
    iret
