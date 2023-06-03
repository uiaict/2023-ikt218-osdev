#include "screen.h"
#include "int.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"
{
    #include "gdt.h"
    #include "idt.h"
    void kernel_main();
}

// ASSIGNMENT 3
void register_three_isr()
{
    // Do this for interrupt 5, 7 and 9
    register_interrupt_handler(5,[](registers_t* regs, void* data){
        terminal_writestring("Interrupt 5 was triggered\n");
    },NULL);
    register_interrupt_handler(7,[](registers_t* regs, void* data){
        terminal_writestring("Interrupt 7 was triggered\n");
    },NULL);
    register_interrupt_handler(9,[](registers_t* regs, void* data){
        terminal_writestring("Interrupt 9 was triggered\n");
    },NULL);
}
void kernel_main()
{
    // ASSIGNMENT 2.1 AND 3.1
    // Initialize the GDT and the IDT
    init_gdt();
    init_idt();

    // Will clear the terminal
    terminal_initialize();
 
    // ASSIGNMENT 2.2
    // Will print the given string to the terminal
	terminal_writestring("Hello World\n\n");

    // ASSIGNMENT 3.2
    // Triggers the three interrupts
    register_three_isr();
    asm volatile ("int $0x5");
    asm volatile ("int $0x7");
    asm volatile ("int $0x9");

    terminal_writestring("\nWaiting for keyboard...\n");
    while(1){};
    terminal_writestring("End");
}
