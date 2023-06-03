#include "common.h"
#include "pit.h"
#include "monitor.h"

volatile uint32_t ticks = 0;
static uint32_t ticks_per_ms = 0;

void timer_callback(registers_t regs)
{
    ticks++;
}

void init_pit()
{
    register_interrupt_handler(IRQ0, timer_callback);

    // Set the PIT frequency by sending the appropriate divisor value
    outb(PIT_CMD_PORT, 0x34); // Set command byte, channel 0, lobyte/hibyte, mode 3
    outb(PIT_CHANNEL0_PORT, PIT_DEFAULT_DIVISOR & 0xFF); // Send low byte of divisor
    outb(PIT_CHANNEL0_PORT, (PIT_DEFAULT_DIVISOR >> 8) & 0xFF); // Send high byte of divisor
    monitor_write("Pit successfully launced\n");
    // Calculate the number of ticks per millisecond
    ticks_per_ms = PIT_BASE_FREQUENCY / TARGET_FREQUENCY;
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
