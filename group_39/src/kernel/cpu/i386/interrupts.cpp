#include "interrupts.h"
#include <stdint.h>
#include "../screen/screen.h"


void isr_handler(registers regs) asm ("isr_handler");


void isr_handler(registers regs)
{
    int a = regs.interrupt_number;
}

void isr0_handler() 
{
    clearScreen();
    printString("Interrupt 0 has occured!");
}


void isr1_handler()
{
    clearScreen();
    printString("Interrupt 1 has occured!");
}


void isr7_handler()
{
    clearScreen();
    printString("Interrupt 7 has occured!");
}