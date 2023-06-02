//
// isr.c -- High level interrupt service routines and interrupt request handlers.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
// http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

#include "common.h"
#include "isr.h"
#include "monitor.h"
#include "print.h"
#include "isr.h"
#include "isr_handlers.h"

isr_t interrupt_handlers[256];

// Function that registers a handler for a given interrupt
void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void init_interrupt_handlers()
{
    // Default 
    for (int i = 0; i < 256; i++)
    {
        register_interrupt_handler(i, *default_isr);
    }

    // Register the ISRs
    register_interrupt_handler(ISR0, *divide_by_zero_isr);
    register_interrupt_handler(ISR1, *debug_isr);
    register_interrupt_handler(ISR2, *non_maskable_interrupt_isr);
    register_interrupt_handler(ISR3, *breakpoint_isr);
    register_interrupt_handler(ISR4, *overflow_isr);
    register_interrupt_handler(ISR5, *bound_range_ex_isr);
    register_interrupt_handler(ISR6, *invalid_opcode_isr);
    register_interrupt_handler(ISR7, *device_not_available_isr);
    register_interrupt_handler(ISR8, *double_fault_isr);
    register_interrupt_handler(ISR9, *coprocessor_segment_overrun_isr);
    register_interrupt_handler(ISR10, *invalid_tss_isr);
    register_interrupt_handler(ISR11, *segment_not_present_isr);
    register_interrupt_handler(ISR12, *stack_segment_fault_isr);
    register_interrupt_handler(ISR13, *general_protection_fault_isr);
    register_interrupt_handler(ISR14, *page_fault_isr);
    register_interrupt_handler(ISR16, *floating_point_error_isr);
    register_interrupt_handler(ISR17, *alignment_check_isr);
    register_interrupt_handler(ISR18, *machine_check_isr);
    register_interrupt_handler(ISR19, *simd_floating_point_isr);
    register_interrupt_handler(ISR20, *virtualization_isr);
}


// The interrupt handler function which is called from the ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    // Check if we have a handler to run for this interrupt
    if (interrupt_handlers[regs.int_no]) 
    {
        printf("Interrupt %d: ", regs.int_no);
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    else // If not, print out a message stating that we have an unhandled interrupt
    {
        printf("Unhandled Interrupt: %d\n", regs.int_no);
    } 
}
