#include "interrupts.h"
#include <stdint.h>
#include "../screen/screen.h"


void isr_default(uint32_t interrupt) asm ("isr_default");
void isr_default(uint32_t interrupt) asm ("isr_default");


void isr_default(uint32_t interrupt)
{
    uint32_t a = interrupt;
    printString("Interrupt occurred!");
    uint32_t b = interrupt;
}



void isr0_handler() 
{

}
