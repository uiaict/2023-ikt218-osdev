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
    print("Recieved interrupt: ");
    write_int_to_terminal(regs.int_no);
} 