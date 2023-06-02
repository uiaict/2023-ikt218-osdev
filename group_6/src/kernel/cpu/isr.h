#include <stdint.h>

// A few defines to make life a little easier
#define ISR1 1
#define ISR2 2
#define ISR3 3


namespace UiAOS::CPU::ISR{

    typedef struct registers
    {
        uint32_t ds;                  // Data segment selector
        uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // Pushed by pusha.
        uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
        uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
    } registers_t;

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
    typedef void (*isr_t)(registers_t*, void*);
    void register_interrupt_handler(uint8_t n, isr_t handler, void*);

// Define handlers
    typedef struct interrupt_handlers_type{
        isr_t handler;
        void* context;
    } interrupt_t;


}