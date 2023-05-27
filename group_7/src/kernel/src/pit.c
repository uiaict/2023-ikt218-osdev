#include "pit.h"
#include "interrupts.h"
#include "system.h"
#include "common.h"

// Pit initializor
void init_pit()
{
    // Register a iterrupt handler when pit interrupt is triggered
    register_irq_handler(IRQ0, [] (registers_t* regs, void* data){
        printf("PIT interrupt\n");
        Tick++;
	}, NULL);

    outb(0x43, 0x36);

    // Split up the divisor into upper and lower bytes
    uint8_t l_divisor = (uint8_t)(1193180 / 1000);
    uint8_t h_divisor = (uint8_t)((1193180 / 1000) >> 8);

    // Send the frequency divisor
    outb(0x40, l_divisor);
    outb(0x40, h_divisor);

}

// void sleep_interrupt(uint32_t milliseconds)
// {

// }

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

static uint32_t Tick = 0;