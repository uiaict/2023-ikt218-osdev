//
// isr.h -- Interface and structures for high level interrupt service routines.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
// http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

#ifndef ISR_H
#define ISR_H

#include "common.h"

#define ISR0  0
#define ISR1  1
#define ISR2  2
#define ISR3  3
#define ISR4  4
#define ISR5  5
#define ISR6  6
#define ISR7  7
#define ISR8  8
#define ISR9  9
#define ISR10 10
#define ISR11 11
#define ISR12 12
#define ISR13 13
#define ISR14 14
#define ISR15 15
#define ISR16 16
#define ISR17 17
#define ISR18 18
#define ISR19 19
#define ISR20 20
#define ISR21 21
#define ISR22 22
#define ISR23 23
#define ISR24 24
#define ISR25 25
#define ISR26 26
#define ISR27 27
#define ISR28 28
#define ISR29 29
#define ISR30 30
#define ISR31 31

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

// Definition of registers structure. Represents the register state during an interrupt
typedef struct registers
{
    u32int ds;                                      // Data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha.
    u32int int_no, err_code;                        // Interrupt number and error code (if applicable)
    u32int eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically.
} registers_t; 

// New type definition, which is a pointer to a function that takes a registers_t as an argument
typedef void (*isr_t)(registers_t);

extern void isr_handler(registers_t regs);

extern void init_interrupt_handlers();

extern isr_t interrupt_handlers[256];

#endif