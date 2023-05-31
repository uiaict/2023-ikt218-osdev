

#ifndef UIAOS_INTERRUPTS_H
#define UIAOS_INTERRUPTS_H

#include <stdint.h>

extern "C" 
{
    extern void isr0 ();
    extern void isr1 ();
    extern void isr2 ();
}



struct registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_number, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
};


#endif