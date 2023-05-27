#include <stdint.h>

// Definition of an interrupt gate
#define ISR0 0
#define ISR1 1
#define ISR2 2

#define IRQ0 3
#define IRQ1 4
#define IRQ2 5
#define IRQ3 6
#define IRQ4 7
#define IRQ5 8
#define IRQ6 9
#define IRQ7 10
#define IRQ8 11
#define IRQ9 12
#define IRQ10 13
#define IRQ11 14
#define IRQ12 15
#define IRQ13 16
#define IRQ14 17
#define IRQ15 18


// Definition of an interrupt gate
namespace UiAOS::CPU::ISR{

    // A struct describing an interrupt gate.
    typedef struct registers
    {
        uint32_t ds;                                                    // Data segment selector           
        uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax;      // Pushed by pusha from interrupt handler
        uint32_t int_no, err_code;                                      // Interrupt number and error code
        uint32_t eip, cs, eflags, esp, ss;                              // Pushed by the cpu automatically
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