#include <interrupts.h>
#include <system.h>

extern "C" {
    void isr_handler(registers regs) asm("isr_handler");
}

void register_interrupt_handler(uint8_t vector, isr_t handler, void* context) {
    int_handlers[vector].handler = handler;
    int_handlers[vector].data = context;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers regs) {
    // This line is important. When the processor extends the 8-bit interrupt number
    // to a 32bit value, it sign-extends, not zero extends. So if the most significant
    // bit (0x80) is set, regs.int_no will be very large (about 0xffffff80).
    uint8_t int_no = regs.int_no & 0xFF;
    int_handler intrpt = int_handlers[int_no];
    if (intrpt.handler != 0) {

        intrpt.handler(&regs, intrpt.data);
        printf("Received interrupt:");
    }
    else {
        printf("unhandled interrupt:");
        for(;;);
    }
}