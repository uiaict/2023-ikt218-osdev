//
// isr.c -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "isr.h"
#include "printing.h"

extern "C" {
    void isr_handler(registers_t);
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    write_to_terminal(1, "recieved interrupt: ");
    write_int_to_terminal(2, regs.int_no);
} 