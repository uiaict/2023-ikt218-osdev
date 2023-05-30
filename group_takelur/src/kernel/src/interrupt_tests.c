#include "interrupt_tests.h"

// Trigger divide by zero exception
int test_divide_by_zero()
{
    asm volatile("int $0x0");
}

// Trigger debug exception by setting the trap flag
void trigger_debug_exception() 
{
    asm volatile("int $0x1");
}

// Trigger breakpoint exception by executing the int3 instruction
void trigger_breakpoint_exception() 
{
    asm volatile("int $0x3");
}

// Trigger invalid opcode exception by executing the ud2 instruction
void trigger_invalid_opcode_exception() 
{
    asm volatile("int $0x6");
}

// Triggers an interrupt I have not created a handler for
void trigger_unhandled_interrupt() 
{
    asm volatile("int $0x1B");   // Triggers interrupt 38, which I only have the default handler for
}