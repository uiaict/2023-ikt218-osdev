#ifndef IRQ_HANDLERS_H
#define IRQ_HANDLERS_H

#include "isr.h"
#include "irq_handlers.h"

extern void timer_handler(registers_t regs);
extern void keyboard_handler(registers_t regs);
extern void cascade_handler(registers_t regs);
extern void com2_handler(registers_t regs);
extern void com1_handler(registers_t regs);
extern void lpt2_handler(registers_t regs);
extern void floppy_disk_handler(registers_t regs);
extern void lpt1_handler(registers_t regs);
extern void cmos_real_time_clock_handler(registers_t regs);
extern void legacy_scsi_or_vga_or_mca_handler(registers_t regs);
extern void scsi_handler(registers_t regs);
extern void scsi_or_ethernet_handler(registers_t regs);
extern void ps2_mouse_handler(registers_t regs);
extern void fpu_coprocessor_handler(registers_t regs);
extern void primary_ata_hard_disk_handler(registers_t regs);
extern void secondary_ata_hard_disk_handler(registers_t regs);

#endif
