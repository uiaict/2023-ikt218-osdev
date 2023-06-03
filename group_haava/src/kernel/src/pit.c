#include "common.h"
#include "interrupts.h"
#include "pit.h"


uint32_t timer_ticks = 0;

static void set_pit_divisor(uint16_t divisor)
{
    output_to_port(PIT_CMD_PORT, 0x36);
    output_to_port(PIT_CHANNEL0_PORT, (uint8_t) (divisor & 0xFF));
    output_to_port(PIT_CHANNEL0_PORT, (uint8_t) (divisor >> 8) & 0xFF);
}

static inline uint32_t ticks_per_ms(uint32_t ms)
{
    return ms * TARGET_FREQUENCY / 1000;
}

static void pit_callback()
{
    timer_ticks++;
}

void pit_init()
{
    set_pit_divisor(PIT_DIVISOR);
    register_irq_handler(IRQ0, pit_callback);
}

void sleep_interrupt(uint32_t milliseconds)
{
    timer_ticks = 0;
    uint32_t ticks_to_wait = ticks_per_ms(milliseconds);
    while (timer_ticks < ticks_to_wait) {
        __asm__("hlt");
    }
}

void sleep_busy(uint32_t milliseconds)
{
    timer_ticks = 0;
    uint32_t ticks_to_wait = ticks_per_ms(milliseconds);
    while (timer_ticks < ticks_to_wait) {}
}
