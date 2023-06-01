// Source: https://wiki.osdev.org/Programmable_Interval_Timer, fetched 23:15, 31.05.2023

#include "include/pit.h"

void pit_interrupt_handler(registers_t* regs, void* data) {
    printf("PIT interrupt triggered.\n");
}

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
    
    // Register PIT interrupt handler
    register_interrupt_handler(IRQ0, pit_interrupt_handler, nullptr);
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

void reset_pit() {
    asm volatile("cli"); // Disable interrups

    outb(PIT_CMD_PORT, 0x36);
    outb(PIT_CHANNEL0_PORT, 0x00);

    asm volatile("sti"); // Enable interrups
}

void sleep_busy(uint32_t milliseconds) {
    reset_pit(); // Reset timer
    uint16_t start_tick = get_tick();

    uint16_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint16_t elapsed_ticks = 0;

    uint16_t current_tick = 0;

    asm volatile("sti"); // Enable interrupts

    while (elapsed_ticks < ticks_to_wait) {
        current_tick = get_tick();
        while (current_tick == start_tick + elapsed_ticks) {
            current_tick = get_tick();    
            asm volatile("nop");
        }
        elapsed_ticks++;
    }
}

void sleep_interrupt(uint32_t milliseconds) {
    reset_pit(); // Reset timer
    uint16_t current_tick = get_tick();

    uint16_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint16_t end_ticks = current_tick + ticks_to_wait;
    


    while (current_tick < end_ticks) {
        asm volatile("sti"); // Enable interrups
        asm volatile("hlt"); // Halt the cpu
        asm volatile("cli"); // Disable interrupts
        current_tick = get_tick(); 
    }   
}
