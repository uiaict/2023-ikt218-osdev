// Source: https://wiki.osdev.org/Programmable_Interval_Timer, fetched 23:15, 31.05.2023

#include "include/pit.h"

void init_pit() {
    // Set command byte to 0x36. 
    // This sets the following configurations:
    // Channel 0
    // Lobyte/Highbyte access
    // Mode 3: Wave generator mode
    outb(PIT_CMD_PORT, 0x36);

    // Set low byte
    outb(PIT_CHANNEL0_PORT, DIVIDER & 0xFF); // Performs a bitwise AND operation on the divisor

    // Set high byte
    outb(PIT_CHANNEL0_PORT, DIVIDER >> 8); // Bit shifts divisor 8 bits to the right
}

void send_EOI() {
    outb(PIC1_CMD_PORT, PIC_EOI);
}

uint16_t get_tick() {

    unsigned count = 0;

    // Disable interrups
    asm volatile("cli");

    // Set Channel 0 to read and clear
    // remaining bits
    outb(PIT_CMD_PORT, 0b0000000);

    // Read low byte and high byte
    count = inb(PIT_CHANNEL0_PORT);          // Low byte
    count |= inb(PIT_CHANNEL0_PORT) << 8;     // High byte
 
    // Enable interrups
    asm volatile("sti");
        
    return count;
}

void sleep_interrupt(uint32_t milliseconds) {
    uint16_t current_tick = get_tick();

    uint16_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint16_t end_ticks = current_tick + ticks_to_wait;

    while (current_tick < end_ticks) {
        // Enable interrups
        asm volatile("sti");
        // Halt the cpu
        asm volatile("hlt");

        current_tick = get_tick();
    }   
}
