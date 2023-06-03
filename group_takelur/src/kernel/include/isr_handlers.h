#ifndef ISR_HANDLERS_H
#define ISR_HANDLERS_H

#include "isr.h"

extern void divide_by_zero_isr(registers_t regs);
extern void debug_isr(registers_t regs);
extern void non_maskable_interrupt_isr(registers_t regs);
extern void breakpoint_isr(registers_t regs);
extern void overflow_isr(registers_t regs);
extern void bound_range_ex_isr(registers_t regs);
extern void invalid_opcode_isr(registers_t regs);
extern void device_not_available_isr(registers_t regs);
extern void double_fault_isr(registers_t regs);
extern void coprocessor_segment_overrun_isr(registers_t regs);
extern void invalid_tss_isr(registers_t regs);
extern void segment_not_present_isr(registers_t regs);
extern void stack_segment_fault_isr(registers_t regs);
extern void general_protection_fault_isr(registers_t regs);
extern void page_fault_isr(registers_t regs);
extern void floating_point_error_isr(registers_t regs);
extern void alignment_check_isr(registers_t regs);
extern void machine_check_isr(registers_t regs);
extern void simd_floating_point_isr(registers_t regs);
extern void virtualization_isr(registers_t regs);
extern void default_isr(registers_t regs);

#endif;
