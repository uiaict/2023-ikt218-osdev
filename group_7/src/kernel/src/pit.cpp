#include "pit.h"
#include <stdint.h>
#include "interrupts.h"
#include "common.h"
#include "system.h"


// Pit initializor
void init_pit()
{
    // Register a iterrupt handler when pit interrupt is triggered
    register_irq_handler(IRQ0, [] (registers_t* regs, void* data){
        Tick++;
	}, NULL);

    outb(0x43, 0x36);

    // Split up the divisor into upper and lower bytes
    uint8_t l_divisor = (uint8_t)(PIT_BASE_FREQUENCY / TARGET_FREQUENCY);
    uint8_t h_divisor = (uint8_t)((PIT_BASE_FREQUENCY / TARGET_FREQUENCY) >> 8);

    // Send the frequency divisor
    outb(0x40, l_divisor);
    outb(0x40, h_divisor);

}

void sleep_interrupt(uint32_t milliseconds)
{
    uint32_t current_tick = Tick;
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t end_ticks = Tick + ticks_to_wait;

    while (current_tick < end_ticks)
    {
        asm volatile("sti");
        asm volatile("hlt");

        current_tick = Tick;
    }
    
}

void sleep_busy(uint32_t milliseconds)
{
    uint32_t start_tick = Tick;
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t elapsed_ticks = 0;

    while (elapsed_ticks < ticks_to_wait)
    {
        while (Tick == start_tick + elapsed_ticks){}
        elapsed_ticks++;
    }
}