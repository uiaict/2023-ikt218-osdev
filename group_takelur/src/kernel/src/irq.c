
#include "common.h"
#include "idt.h"
#include "isr.h"
#include "monitor.h"
#include "print.h"
#include "irq_handlers.h"

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
