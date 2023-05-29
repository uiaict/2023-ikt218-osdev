#include "interrupt_tests.h"

// Trigger divide by zero exception
int test_divide_by_zero(int a)
{
    return a / 0;
}

// Trigger debug exception by setting the trap flag
void trigger_debug_exception() 
{
    __asm__("pushf\n"
            "orl $0x100, (%esp)\n"
            "popf\n");
}

// Trigger breakpoint exception by executing the int3 instruction
void trigger_breakpoint_exception() 
{
    __asm__("int3");
}

// Trigger invalid opcode exception by executing the ud2 instruction
void trigger_invalid_opcode_exception() 
{
    __asm__("ud2");
}

// Triggers an interrupt I have not created a handler for
void trigger_unhandled_interrupt() 
{
    __asm__("int $0x1B");   // Triggers interrupt 38, which I only have the default handler for
}