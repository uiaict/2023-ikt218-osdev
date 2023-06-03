#include "pit.h"
#include "common.h"
#include <system.h>
#include "idt.h"

void init_pit()
{
    register_irq_handler(IRQ0, [](registers*, void*) {
        ticks++;
    }, NULL);

    // Set the command byte.
    outb(PIT_CMD_PORT, 0x34);

    // Set the frequency divisor.
    outb(PIT_CHANNEL0_PORT, DIVIDER & 0xFF);  // Lower byte.
    outb(PIT_CHANNEL0_PORT, (DIVIDER >> 8) & 0xFF);  // Upper byte.
}

uint32_t get_current_tick()
{
    return ticks;
}

void sleep_interrupt(uint32_t milliseconds) 
{
    uint32_t current_tick = get_current_tick();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t end_ticks = current_tick + ticks_to_wait;

    while (current_tick < end_ticks) {
        asm volatile("sti");
        asm volatile("hlt");
        current_tick = get_current_tick();
    }
}

void sleep_busy(uint32_t milliseconds)
{
    uint32_t start_tick = get_current_tick();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t elapsed = 0;

    while (elapsed < ticks_to_wait) {
        while(get_current_tick() == start_tick + elapsed) {
            // busy wait
        }
        elapsed++;
    }
}