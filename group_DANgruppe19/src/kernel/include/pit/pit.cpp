
/*
#include "pit.h"
// use inb, outb functions.

volatile uint32_t tick = 0;

extern "C" {
    // This function will be called from the interrupts' code
    void pit_irq() {
        tick = (volatile uint32_t)((uint32_t)tick + 1);
        outb(PIC1_CMD_PORT, PIC_EOI);
    }
}

void init_pit() {
    // Set the PIC to operate in mode 3
    outb(PIT_CMD_PORT, 0x36);

    // Set the divisor
    outb(PIT_CHANNEL0_PORT, (uint8_t) (DIVIDER & 0xFF));
    outb(PIT_CHANNEL0_PORT, (uint8_t) ((DIVIDER >> 8) & 0xFF));

    // Enable IRQ0 in the PIC
    outb(PIC1_DATA_PORT, inb(PIC1_DATA_PORT) & ~1);

    // ... and set the IRQ0 handler
    // You need to replace "set_idt_gate" and "0x21" with your own functions/definitions.
    idt_set_gate(0x21, (uint32_t) pit_irq);
}

void sleep_busy(uint32_t milliseconds) {
    uint32_t target_tick = tick + milliseconds * TICKS_PER_MS;
    while (tick < target_tick) {
        asm volatile("nop");
    }
}

void sleep_interrupt(uint32_t milliseconds) {
    uint32_t target_tick = tick + milliseconds * TICKS_PER_MS;
    while (tick < target_tick) {
        asm volatile("sti\nhlt\ncli");
    }
}


void printfun(const char* str, ...) {
    char buffer[50];
    va_list args;
    va_start(args, str);

    while (*str) {
        if (*str == '%') {
            str++;
            if (*str == 'd') {
                int value = va_arg(args, int);
                int size = print_int(buffer, value);
                terminal_write(buffer, size);
            }
        } else {
            buffer[0] = *str;
            terminal_write(buffer, 1);
        }
        str++;
    }

    va_end(args);
}
*/