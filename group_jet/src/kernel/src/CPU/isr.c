#include "isr.h"
#include "system.h"


// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
   terminal_writestring("recieved interrupt: ");
   terminal_writedecimal(regs.int_no);
}