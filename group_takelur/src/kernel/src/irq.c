
#include "common.h"
#include "idt.h"
#include "isr.h"
#include "monitor.h"
#include "print.h"
#include "irq_handlers.h"

// This function is used to send an EOI signal to the PICs
void irq_ack(int irq) {
    if (irq >= 8) 
        outb(0xA0, 0x20);    // Send EOI to slave PIC
    outb(0x20, 0x20);        // Send EOI to master PIC
}

// Initialize irq handlers (overwrite default handlers)
void init_irq_handlers()
{
    register_interrupt_handler(IRQ0, *timer_handler);
    register_interrupt_handler(IRQ1, *keyboard_handler);
    register_interrupt_handler(IRQ2, *cascade_handler);
    register_interrupt_handler(IRQ3, *com2_handler);
    register_interrupt_handler(IRQ4, *com1_handler);
    register_interrupt_handler(IRQ5, *lpt2_handler);
    register_interrupt_handler(IRQ6, *floppy_disk_handler);
    register_interrupt_handler(IRQ7, *lpt1_handler);
    register_interrupt_handler(IRQ8, *cmos_real_time_clock_handler);
    register_interrupt_handler(IRQ9, *legacy_scsi_or_vga_or_mca_handler);
    register_interrupt_handler(IRQ10, *scsi_handler);
    register_interrupt_handler(IRQ11, *scsi_or_ethernet_handler);
    register_interrupt_handler(IRQ12, *ps2_mouse_handler);
    register_interrupt_handler(IRQ13, *fpu_coprocessor_handler);
    register_interrupt_handler(IRQ14, *primary_ata_hard_disk_handler);
    register_interrupt_handler(IRQ15, *secondary_ata_hard_disk_handler);
}

void irq_handler(registers_t regs)
{
    // Check if we have a custom handler to run for this interrupt
    if (interrupt_handlers[regs.int_no] && regs.int_no >= 32)
    {
        // Do not print the PIT interrupt or keyboard interrupt due to spam
        if (regs.int_no != 32 && regs.int_no != 33)
            printf("Interrupt %d: ", regs.int_no);
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    else // If not, print out a message stating that we have an unhandled interrupt
    {
        printf("Unhandled Interrupt: %d\n", regs.int_no);
    }

    // ACK the interrupt
    irq_ack(regs.int_no - 32); // - 32 because IRQ0 maps to IDT entry 32
}