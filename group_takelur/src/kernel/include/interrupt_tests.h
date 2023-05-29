#ifndef INTERRUPT_TESTS_H
#define INTERRUPT_TESTS_H

extern int test_divide_by_zero(int a);

extern void trigger_debug_exception();

extern void trigger_breakpoint_exception();

extern void trigger_invalid_opcode_exception();

extern void trigger_unhandled_interrupt();

#endif