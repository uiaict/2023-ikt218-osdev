#include "interrupts.h"
#include <stdint.h>
#include "../screen/screen.h"


void isr_handler(registers regs) asm ("isr_default");


void isr_handler(registers regs)
{
    int a = regs.interrupt_number;

}

void isr0_handler() 
{

}
