#include "timer.h"
#include "ports.h"
#include "isr.h"
#include "../drivers/screen.h"


uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;

    // Toggle the cursor on and off by XORing the cursor end register with 0x80.
    uint8_t cursor_end = inb(0x3D5);
    outb(0x3D4, 0x0B); // cursor end register
    outb(0x3D5, cursor_end ^ 0x80);
}

void load_timer(uint32_t frequency)
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, low);
    outb(0x40, high);
}