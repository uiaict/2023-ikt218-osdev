#include <kernel/pit.h>
#include <hardware_port.h>
#include <screen.h>
#include <cpu/isr.h>
#include <stddef.h>

uint32_t timer_tick = 0;

void init_pit(){
    // System timer
    register_irq_handler(IRQ0, pit_handler, NULL);

    outb(PIT_CMD_PORT, 0x36);   // Set port value to the destination port
    uint8_t l = (uint8_t)(DIVIDER & BITMASK);
    uint8_t h = (uint8_t)((DIVIDER >> 8) & BITMASK);

    outb(PIT_CHANNEL0_PORT, l);
    outb(PIT_CHANNEL0_PORT, h);
}

// Increments the ticks
void pit_handler() {
    timer_tick++;
}

// Function: sleep_busy
void sleep_busy(uint32_t milliseconds) {
    printf("Sleep engaged!\n");
    uint32_t start_tick = timer_tick;
    uint32_t elapsed_ticks = 0;
    uint32_t eticks = milliseconds * TICKS_PER_MS;  // Calculate the number of elapsed ticks based on the desired milliseconds delay

    while (elapsed_ticks < eticks) {
        // Do nothing and wait for the desired time to pass
        if (timer_tick != start_tick) {
            // A tick has occurred, increment the elapsed_ticks counter
            elapsed_ticks++;
            start_tick = timer_tick;
        }
    }
    printf("Sleep finished!\n");
}

// Function: sleep_interrupt
void sleep_interrupt(uint32_t milliseconds) {
    uint32_t current_tick = timer_tick;
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;


    while (current_tick < ticks_to_wait) {
        // Execute the following assembly instructions:
        asm volatile("sti");  // Enable interrupts
        asm volatile("hlt");  // Halt the CPU until the next interrupt

        ticks_to_wait--;
    }
}