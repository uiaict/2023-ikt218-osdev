#include "../include/pit.h"
#include "../include/isr.h"
#include "../include/monitor.h"
#include "../include/common.h"
#include "../include/descriptor_tables.h"

u32int tick = 0;

static void timer_callback(registers_t regs)
{
   tick++;
   monitor_write("Tick: ");
   monitor_write_dec(tick);
   monitor_write("\n");
}


void init_timer(u32int frequency)
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int low = (u8int)(divisor & 0xFF);                           
    u8int hight = (u8int)( (divisor>>8) & 0xFF );

   

    // Send the frequency divisor.
    outb(0x40, low);
    outb(0x40, hight);
}