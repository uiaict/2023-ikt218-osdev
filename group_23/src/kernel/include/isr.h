#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include "common.h"
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
#define ISR_SIZE 256


//store registers in processor
typedef struct registers
{
    uint32_t ds;                                     //data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //registers to store data during program execution
    uint32_t int_no, err_code;                       //interrupt number and error code registers, store info related to interrupts during program execution
    uint32_t eip, cs, eflags, useresp, ss;           //registers pushed to stack by processor automatically if interrupt or exception occurs 
                                                     //eip: instruction pointer, cs: code segment, eflags: flags register, useresp: stack pointer, ss: stack segment

} registers_t;



void isr_handler(registers_t regs);                  //interrupt service routine handler to handle interrupts
typedef void (*isr_t)(registers_t);                  //pointer to function isr_t that takes registers_t as argument 
void register_interrupt_handler(uint8_t n, isr_t handler);


#endif