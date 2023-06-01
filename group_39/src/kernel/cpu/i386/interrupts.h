

#ifndef UIAOS_INTERRUPTS_H
#define UIAOS_INTERRUPTS_H

#include <stdint.h>


extern "C"
{
    extern void isr0();
    extern void isr1();
    extern void isr7();
    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();
}



void default_isr();


struct registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_number, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void keyboard_handler(registers regs);

#endif