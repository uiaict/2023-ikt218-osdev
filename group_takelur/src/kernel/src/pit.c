#include "pit.h"
#include "common.h"

// Reference: http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html

// Volatile means no optimizations from compiler
volatile u32int tick = 0;

static void get_current_tick()
{
    return tick;
}

// Initialize the PIT (Programmable Interval Timer)
void init_pit()
{
    u32int divisor = PIT_DEFAULT_DIVISOR;

    // Send the command byte
    outb(PIT_CMD_PORT, 0x36);

    // Split the divisor into two bytes: lower and upper. This is because the divisor is 16 bits and has to be sent bytewise.
    u8int low = (u8int)(divisor & 0xFF);
    u8int high = (u8int)((divisor >> 8) & 0xFF);

    // Finally send the divisor bytes
    outb(PIT_CHANNEL0_PORT, low);
    outb(PIT_CHANNEL0_PORT, high);
}

// Sleep function utilizing the PIT interrupts
void sleep_interrupt(uint32_t milliseconds)
{
    u32int current_tick = get_current_tick();
    u32int ticks_to_wait = milliseconds * TICKS_PER_MS;
    u32int final_tick = current_tick + ticks_to_wait;

    while (current_tick < final_tick)
    {
        asm volatile("sti");
        asm volatile("hlt");    // halts until next interrupt (saves CPU cycles)
        current_tick = get_current_tick();
    }
}

// Sleep function utilizing busy waiting
void sleep_busy(uint32_t milliseconds)
{
    u32int start_tick = get_current_tick();
    u32int ticks_to_wait = milliseconds * TICKS_PER_MS;
    u32int elapsed_ticks = 0;

    while (elapsed_ticks < ticks_to_wait)
    {
        while (get_current_tick() == start_tick + elapsed_ticks)
        {
            // Busy wait...
        }
        elapsed_ticks++;
    }
}
