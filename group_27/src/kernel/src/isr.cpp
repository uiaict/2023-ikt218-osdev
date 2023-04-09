//
// isr.c
// This code contains interrupt request handlers and service routines
//

#include "common.h"
#include "isr.h"
#include "printing.h"

extern "C" {
    void isr_handler(registers_t);
}

// Gets called from interrupt.asm
// Writes the interrupts to the screen
void isr_handler(registers_t regs)
{
    write_to_terminal(1, "recieved interrupt: ");
    write_int_to_terminal(2, regs.int_no);
} 