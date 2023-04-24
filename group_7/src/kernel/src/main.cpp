#include "gdt.h"
#include "idt.h"
#include "interrupts.h"
#include <cstddef>
#include <stdint.h>
#include <cstdlib>
#include "common.h"
#include "keyboard.h"


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
    demo_interrupts();
    
    // Register the IRQ1, keyboard, interrupt handler:
    keyboard_handler();

    // This will trigger the ISR1 interrupt:
    //asm volatile("int $0x01");
    
    asm volatile("sti");
    
    printf("Hello World\n");

    while (1){}
    
}
