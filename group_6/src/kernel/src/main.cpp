#include "system.h"
#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../screen/screen.h"
#include "../cpu/isr.h"

namespace ISR = UiAOS::CPU::ISR;

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();

}

void kernel_main() {
 
    write_string(0xF, "Hello, world!");

    // clear_screen(160);  


    // Functioncall for interrupt handler
    ISR::register_interrupt_handler(ISR1, [](ISR::registers_t* regs, void* context){
        write_string(0xF, "Interrupt 1 triggered");
    },NULL);

    ISR::register_interrupt_handler(ISR2, [](ISR::registers_t* regs, void* context){
        write_string(0xF, "Interrupt 2 triggered");
    },NULL);
    
    ISR::register_interrupt_handler(ISR3, [](ISR::registers_t* regs, void* context){
        write_string(0xF, "Interrupt 3 triggered");
    },NULL);
    
    // Triggers
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");
    asm volatile ("int $0x3");    
}
