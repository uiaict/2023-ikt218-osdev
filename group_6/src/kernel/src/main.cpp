#include "system.h"
#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../screen/screen.h"
#include "../cpu/isr.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();

}


void kernel_main() {
 
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");
    write_string(0xF, "Hello, world!");

    UiAOS::CPU::ISR::register_interrupt_handler(ISR1, [](UiAOS::CPU::ISR::registers_t* regs, void* context){
        write_string(0xF, "Interrupt 1 triggered");
    },NULL);
    
    asm volatile ("int $0x1");

    
}
