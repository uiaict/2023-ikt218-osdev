#include "interrupts.h"
#include <stdint.h>
#include "idt.h"
#include "../screen/screen.h"
#include "../../common/common.h"


void isr_handler(registers regs) asm ("isr_handler");
void irq_handler(registers regs) asm ("irq_handler");

void isr0_handler();
void isr1_handler();
void isr7_handler();
void keyboard_handler(registers regs);



void isr_handler(registers regs)
{
    uint8_t interrupt_number = regs.interrupt_number & 0xFF;
}

void default_isr()
{
    clearScreen();
    printString("This interrupt is not implemented yet!");
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


void keyboard_handler(registers regs)
{
    int scancode = inb(0x60);
    int a = 5;
    int b = 10;
}
