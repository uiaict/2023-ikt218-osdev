#include "gdt.h"
#include "idt.h"
#include "interrupts.h"
#include <cstddef>
#include <stdint.h>
#include <cstdlib>
#include "common.h"
// Define entry point in asm to prevent C++ mangling
extern "C"{
    // Calls the kernel_main assembly function.
    #include "system.h"

    void kernel_main();
}


/// @brief The kernel main function.
void kernel_main()
{
    // Clear the screen
    clearScreen();
    
    
    // Initialize the global descriptor table:
    init_gdt();
    // Initialize the interrupt descriptor table:
    init_idt();

    init_irq();
    

    // Initialize the interrupt service routines:
    
    // Register the ISR1 interrupt handler:
    register_interrupt_handler(ISR1, [](registers_t* regs, void* data)
    {
        printf("Is this working?\nThe ISR1 got triggered\n");
    }, NULL);
    
    // Register the IRQ1, keyboard, interrupt handler:
    register_interrupt_handler(IRQ1, [](registers_t* regs, void* data)
    {
        uint8_t scancode = inb(0x60);
        //asm volatile("cli");
        printf("Is this working?\n");
        printf("Scancode: %i", scancode);
    }, NULL);

    
    //asm volatile("sti");
    
    printf("Hello World\n");

    asm volatile("int $0x20");

    while (1){}
    
}
