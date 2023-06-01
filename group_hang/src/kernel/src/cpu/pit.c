#include "common.h"
#include "pit.h"
#include "isr.h"
#include "monitor.h"
#include <stdint.h>


volatile uint32_t g_timer_ticks = 0;
static uint32_t ticks_per_ms = 0;

void play_sound(uint32_t frequency)
{
    uint32_t divisor = PIT_BASE_FREQUENCY / frequency;

    // Set the PIT frequency by sending the appropriate divisor value
    outb(PIT_CMD_PORT, 0xB6); // Set command byte, channel 2, lobyte/hibyte, mode 3
    outb(PIT_CHANNEL2_PORT, divisor & 0xFF); // Send low byte of divisor
    outb(PIT_CHANNEL2_PORT, (divisor >> 8) & 0xFF); // Send high byte of divisor

    // Enable PC speaker output
    uint8_t prev = inb(PC_SPEAKER_PORT);
    if ((prev & 0x03) != 0x03)
        outb(PC_SPEAKER_PORT, prev | 0x03);
}

void stop_sound()
{
    // Disable PC speaker output
    uint8_t prev = inb(PC_SPEAKER_PORT);
    if ((prev & 0x03) != 0x00)
        outb(PC_SPEAKER_PORT, prev & 0xFC);
}

void timer_callback(registers_t regs)
{
    g_timer_ticks++;
    play_sound(440); // Play a sound at 440 Hz
    // You can adjust the frequency or use different frequencies for different ticks
}

void init_pit()
{
    register_interrupt_handler(IRQ0, &timer_callback);

    // Set the PIT frequency by sending the appropriate divisor value
    outb(PIT_CMD_PORT, 0x36); // Set command byte, channel 0, lobyte/hibyte, mode 3
    outb(PIT_CHANNEL0_PORT, PIT_DEFAULT_DIVISOR & 0xFF); // Send low byte of divisor
    outb(PIT_CHANNEL0_PORT, (PIT_DEFAULT_DIVISOR >> 8) & 0xFF); // Send high byte of divisor

    // Calculate the number of ticks per millisecond
    ticks_per_ms = PIT_BASE_FREQUENCY / TARGET_FREQUENCY;
}

static uint32_t get_current_tick()
{
    return g_timer_ticks;
}

void sleep_interrupt(uint32_t milliseconds)
{
    int tick_low = 0;
    int ticks_to_wait = milliseconds * ticks_per_ms;

    while (tick_low < ticks_to_wait)
    {
        asm volatile("sti"); // Enable interrupts
        asm volatile("hlt"); // Halt the CPU until the next interrupt
        ticks_to_wait--;
    }
    monitor_write("tick\n");

    stop_sound(); // Stop playing sound after the delay
}
