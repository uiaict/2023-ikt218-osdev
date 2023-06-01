#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "int.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

// ASSIGNMENT 3
void register_three_isr()
{
    // Do this for interrupt 5, 7 and 9
    register_interrupt_handler(5,[](registers_t* regs, void* data){
        terminal_writestring("Interrupt 5 was triggered");
    },NULL);
    register_interrupt_handler(7,[](registers_t* regs, void* data){
        terminal_writestring("Interrupt 7 was triggered");
    },NULL);
    register_interrupt_handler(9,[](registers_t* regs, void* data){
        terminal_writestring("Interrupt 9 was triggered");
    },NULL);
}
void kernel_main()
{
    // Initialization
    init_idt();

    // Will clear the terminal
    terminal_initialize();
 
    // Will print the given string to the terminal
	terminal_writestring("Hello World");

    // Triggers the three interrupts
    register_three_isr();
    asm volatile ("int $0x5");
    asm volatile ("int $0x7");
    asm volatile ("int $0x9");

    terminal_writestring("Wait for keyboard...");
    while(1){};
    terminal_writestring("End");
}
