#include "interrupts.h"
#include <stdint.h>
#include "../screen/screen.h"


void isr_handler(registers regs) asm ("isr_handler");

void isr0_handler();
void isr1_handler();
void isr7_handler();


void isr_handler(registers regs)
{
    uint8_t interrupt_number = regs.interrupt_number & 0xFF;
    switch (interrupt_number)
    {
        case 0:
            isr0_handler();
            break;
        case 1:
            isr1_handler();
            break;
        case 7:
            isr7_handler();
            break;
        default:
            clearScreen();
            printString("Unknown interrupt has occured!");
            break;
    }
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