//
// Created by per on 1/1/23.
//
#include "../hardware_port.h"
#include "../isr.h"


#include "timer.h"

uint32_t tick = 0;


/// This initialises the PIT timer which is found at IRQ 0
/// \param freq - Which frequence (hz) the timer should run at
/// \param handler - The callback handler
/// \param context  - Context you wish to have in the callback handler
void UiAOS::CPU::PIT::init_timer(uint32_t freq, UiAOS::CPU::ISR::isr_t handler, void* context) {
    // Firstly, register our timer callback.
    UiAOS::CPU::ISR::register_interrupt_handler(IRQ0, handler, context);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / freq;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    auto l = (uint8_t)(divisor & 0xFF);
    auto h = (uint8_t)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}