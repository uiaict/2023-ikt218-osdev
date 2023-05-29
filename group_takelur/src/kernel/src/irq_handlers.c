#include "irq_handlers.h"
#include "isr.h"
#include "print.h"
#include "keyboard.h"

void timer_handler(registers_t regs)
{
    // Commented due to spam
    //printf("IRQ0: Timer interrupt fired\n");
}

// Passes the registers to the keyboard controller
void keyboard_handler(registers_t regs)
{
    keyboard_processing(regs);
}

void cascade_handler(registers_t regs)
{
    printf("IRQ2: Cascade interrupt fired\n");
}

void com2_handler(registers_t regs)
{
    printf("IRQ3: COM2 interrupt fired\n");
}

void com1_handler(registers_t regs)
{
    printf("IRQ4: COM1 interrupt fired\n");
}

void lpt2_handler(registers_t regs)
{
    printf("IRQ5: LPT2 interrupt fired\n");
}

void floppy_disk_handler(registers_t regs)
{
    printf("IRQ6: Floppy Disk interrupt fired\n");
}

void lpt1_handler(registers_t regs)
{
    printf("IRQ7: LPT1 interrupt fired\n");
}

void cmos_real_time_clock_handler(registers_t regs)
{
    printf("IRQ8: CMOS Real-Time Clock interrupt fired\n");
}

void legacy_scsi_or_vga_or_mca_handler(registers_t regs)
{
    printf("IRQ9: Legacy SCSI or VGA or MCA interrupt fired\n");
}

void scsi_handler(registers_t regs)
{
    printf("IRQ10: SCSI interrupt fired\n");
}

void scsi_or_ethernet_handler(registers_t regs)
{
    printf("IRQ11: SCSI or Ethernet interrupt fired\n");
}

void ps2_mouse_handler(registers_t regs)
{
    printf("IRQ12: PS/2 Mouse interrupt fired\n");
}

void fpu_coprocessor_handler(registers_t regs)
{
    printf("IRQ13: FPU Coprocessor interrupt fired\n");
}

void primary_ata_hard_disk_handler(registers_t regs)
{
    printf("IRQ14: Primary ATA Hard Disk interrupt fired\n");
}

void secondary_ata_hard_disk_handler(registers_t regs)
{
    printf("IRQ15: Secondary ATA Hard Disk interrupt fired\n");
}
