#include "isr_handlers.h"
#include "isr.h"
// Implementing a few interrupt handlers, with no other functionality than printing out a message.
// In this simple OS, we just print out a message indicating which interrupt occured.
void divide_by_zero_isr(registers_t regs)
{
    printf("Divide by zero occured\n");
}
void debug_isr(registers_t regs)
{
    printf("Debug exception\n");
}
void non_maskable_interrupt_isr(registers_t regs)
{
    printf("Non-maskable-interrupt exception\n");
}
void breakpoint_isr(registers_t regs)
{
    printf("Breakpoint instruction occured\n");
}
void overflow_isr(registers_t regs)
{
    printf("OF flag set exception\n");
}
void bound_range_ex_isr(registers_t regs)
{
    printf("Bound range exceeded exception\n");
}
void invalid_opcode_isr(registers_t regs)
{
    printf("Invalid instruction opcode exception\n");
}
void device_not_available_isr(registers_t regs)
{
    printf("Device not available exception\n");
}
void double_fault_isr(registers_t regs)
{
    printf("Double fault exception\n");
}
void coprocessor_segment_overrun_isr(registers_t regs)
{
    printf("Coprocessor segment overrun exception\n");
}
void invalid_tss_isr(registers_t regs)
{
    printf("Invalid TSS exception\n");
}
void segment_not_present_isr(registers_t regs)
{
    printf("Segment not present exception\n");
}
void stack_segment_fault_isr(registers_t regs)
{
    printf("Stack segment fault exception\n");
}
void general_protection_fault_isr(registers_t regs)
{
    printf("General protection fault exception\n");
}
void page_fault_isr(registers_t regs)
{
    printf("Page fault exception\n");
}
void floating_point_error_isr(registers_t regs)
{
    printf("Floating point error exception\n");
}
void alignment_check_isr(registers_t regs)
{
    printf("Alignment check exception\n");
}
void machine_check_isr(registers_t regs)
{
    printf("Machine check exception\n");
}
void simd_floating_point_isr(registers_t regs)
{
    printf("SIMD floating point exception\n");
}
void virtualization_isr(registers_t regs)
{
    printf("Virtualization exception\n");
}
void default_isr(registers_t regs)
{
    printf("Unhandled interrupt\n");
}