#include "monitor.h"
#include "isr.h"
#include "descriptor_tables.h"
#include "common.h"
#include "pit.h"
isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void divide_by_zero_isr(registers_t regs)
{
    monitor_write("Divide by zero occurred\n");
    monitor_put('\n');
}

void debug_isr(registers_t regs)
{
    monitor_write("Debug exception\n");
    monitor_put('\n');
}

void non_maskable_interrupt_isr(registers_t regs)
{
    monitor_write("Non-maskable-interrupt exception\n");
    monitor_put('\n');
}

void breakpoint_isr(registers_t regs)
{
    monitor_write("Breakpoint instruction occurred\n");
    monitor_put('\n');
}

void overflow_isr(registers_t regs)
{
    monitor_write("OF flag set exception\n");
    monitor_put('\n');
}

void bound_range_ex_isr(registers_t regs)
{
    monitor_write("Bound range exceeded exception\n");
    monitor_put('\n');
}

void invalid_opcode_isr(registers_t regs)
{
    monitor_write("Invalid instruction opcode exception\n");
    monitor_put('\n');
}

void device_not_available_isr(registers_t regs)
{
    monitor_write("Device not available exception\n");
    monitor_put('\n');
}

void double_fault_isr(registers_t regs)
{
    monitor_write("Double fault exception\n");
    monitor_put('\n');
}

void coprocessor_segment_overrun_isr(registers_t regs)
{
    monitor_write("Coprocessor segment overrun exception\n");
    monitor_put('\n');
}

void invalid_tss_isr(registers_t regs)
{
    monitor_write("Invalid TSS exception\n");
    monitor_put('\n');
}

void segment_not_present_isr(registers_t regs)
{
    monitor_write("Segment not present exception\n");
    monitor_put('\n');
}

void stack_segment_fault_isr(registers_t regs)
{
    monitor_write("Stack segment fault exception\n");
    monitor_put('\n');
}

void general_protection_fault_isr(registers_t regs)
{
    monitor_write("General protection fault exception\n");
    monitor_put('\n');
}

void page_fault_isr(registers_t regs)
{
    monitor_write("Page fault exception\n");
    monitor_put('\n');
}

void floating_point_error_isr(registers_t regs)
{
    monitor_write("Floating point error exception\n");
    monitor_put('\n');
}

void alignment_check_isr(registers_t regs)
{
    monitor_write("Alignment check exception\n");
    monitor_put('\n');
}

void machine_check_isr(registers_t regs)
{
    monitor_write("Machine check exception\n");
    monitor_put('\n');
}

void simd_floating_point_isr(registers_t regs)
{
    monitor_write("SIMD floating point exception\n");
    monitor_put('\n');
}

void virtualization_isr(registers_t regs)
{
    monitor_write("Virtualization exception\n");
    monitor_put('\n');
}

void default_isr(registers_t regs)
{
    monitor_write("Unhandled interrupt\n");
    monitor_put('\n');
}


char scancode_to_ascii[] = {
    0,   0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};


void keyboard_isr(registers_t regs)
{
    u8int scancode = inb(0x60);
    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii_char = scancode_to_ascii[scancode];

        if (ascii_char >= ' ' && ascii_char <= '~') {
            monitor_put(ascii_char);
        }
    }
}

void init_interrupt_handlers()
{
    for (int i = 0; i < 256; i++)
    {
        register_interrupt_handler(i, default_isr);
    }
    // Register the isrs
    register_interrupt_handler(0, divide_by_zero_isr);
    register_interrupt_handler(1, debug_isr);
    register_interrupt_handler(2, non_maskable_interrupt_isr);
    register_interrupt_handler(3, breakpoint_isr);
    register_interrupt_handler(4, overflow_isr);
    register_interrupt_handler(5, bound_range_ex_isr);
    register_interrupt_handler(6, invalid_opcode_isr);
    register_interrupt_handler(7, device_not_available_isr);
    register_interrupt_handler(8, double_fault_isr);
    register_interrupt_handler(9, coprocessor_segment_overrun_isr);
    register_interrupt_handler(10, invalid_tss_isr);
    register_interrupt_handler(11, segment_not_present_isr);
    register_interrupt_handler(12, stack_segment_fault_isr);
    register_interrupt_handler(13, general_protection_fault_isr);
    register_interrupt_handler(14, page_fault_isr);
    register_interrupt_handler(16, floating_point_error_isr);
    register_interrupt_handler(17, alignment_check_isr);
    register_interrupt_handler(18, machine_check_isr);
    register_interrupt_handler(19, simd_floating_point_isr);
    register_interrupt_handler(20, virtualization_isr);
    register_interrupt_handler(33, keyboard_isr);  // IRQ1 corresponds to interrupt 33
}

void isr_handler(registers_t regs)
{
    if (regs.int_no < 32) {
        monitor_write("Interrupt");
        monitor_put('\n');

        switch (regs.int_no) {
            case 0:
                divide_by_zero_isr(regs);
                break;
            case 1:
                debug_isr(regs);
                break;
            case 2:
                non_maskable_interrupt_isr(regs);
                break;
            case 3:
                breakpoint_isr(regs);
                break;
            case 4:
                overflow_isr(regs);
                break;
            case 5:
                bound_range_ex_isr(regs);
                break;
            case 6:
                invalid_opcode_isr(regs);
                break;
            case 7:
                device_not_available_isr(regs);
                break;
            case 8:
                double_fault_isr(regs);
                break;
            case 9:
                coprocessor_segment_overrun_isr(regs);
                break;
            case 10:
                invalid_tss_isr(regs);
                break;
            case 11:
                segment_not_present_isr(regs);
                break;
            case 12:
                stack_segment_fault_isr(regs);
                break;
            case 13:
                general_protection_fault_isr(regs);
                break;
            case 14:
                page_fault_isr(regs);
                break;
            case 16:
                floating_point_error_isr(regs);
                break;
            case 17:
                alignment_check_isr(regs);
                break;
            case 18:
                machine_check_isr(regs);
                break;
            case 19:
                simd_floating_point_isr(regs);
                break;
            case 20:
                virtualization_isr(regs);
                break;
            default:
                default_isr(regs);
        }
    } else {
        monitor_write("Unhandled Interrupt");
        monitor_put('\n');
    }
}



void irq_handler(registers_t regs)
{

    if (regs.int_no >= 40)
    {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    if (regs.int_no == IRQ1) {
        keyboard_isr(regs);  // Call the keyboard ISR directly
    }


    if (regs.int_no == IRQ0) {
        timer_callback(regs);  // Call the PIT timer callback directly
    }
    
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}