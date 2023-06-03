#ifndef ISR_H
#define ISR_H
#include "descriptor_tables.h"
#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct registers
{
   u32int ds;                  
   u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; 
   u32int int_no, err_code;    
   u32int eip, cs, eflags, useresp, ss; 
} registers_t; 

typedef void (*isr_t)(registers_t);

void register_interrupt_handler(u8int n, isr_t handler); 
void isr_handler(registers_t regs);
void irq_handler(registers_t regs);
void divide_by_zero_isr(registers_t regs);
void debug_isr(registers_t regs);
void debug_isr(registers_t regs);
void non_maskable_interrupt_isr(registers_t regs);
void breakpoint_isr(registers_t regs);
void overflow_isr(registers_t regs);
void bound_range_ex_isr(registers_t regs);
void invalid_opcode_isr(registers_t regs);
void device_not_available_isr(registers_t regs);
void double_fault_isr(registers_t regs);
void coprocessor_segment_overrun_isr(registers_t regs);
void invalid_tss_isr(registers_t regs);
void segment_not_present_isr(registers_t regs);
void stack_segment_fault_isr(registers_t regs);
void general_protection_fault_isr(registers_t regs);
void page_fault_isr(registers_t regs);
void floating_point_error_isr(registers_t regs);
void alignment_check_isr(registers_t regs);
void machine_check_isr(registers_t regs);
void simd_floating_point_isr(registers_t regs);
void virtualization_isr(registers_t regs);

void default_isr(registers_t regs);
#endif