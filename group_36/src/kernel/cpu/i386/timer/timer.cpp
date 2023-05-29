#include "../hardware_port.h"
#include "../isr.h"
#include "timer.h"

uint32_t tick = 0;

void PIT::init_timer(uint32_t freq, isr_t handler, void* context) {
    
    register_interrupt_handler(IRQ0, handler, context);

    uint32_t divisor = 1193180 / freq;

    outb(0x43, 0x36);

    auto l = (uint8_t)(divisor & 0xFF);
    auto h = (uint8_t)( (divisor>>8) & 0xFF );

    outb(0x40, l);
    outb(0x40, h);
}