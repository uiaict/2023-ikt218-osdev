// Written by Group 39 IKT218 Project Spring 2023.

#include "../screen/screen.h"
#include "../cpu/i386/isr.h"
#include "../cpu/i386/interrupts.h"

// This enables assembly code to call our kernel_main function. 
extern "C" {
    void kernel_main();
}


void kernel_main()
{

    // Register keyboard handler
    register_interrupt_handler(IRQ1, &keyboard_handler);

    asm volatile ("sti"); // Enable interrupts


    clearScreen(); // Clear screen before writing output.

    printString("Hello World"); // Write "Hello World" to the screen.






    while(1){}; // Loop
}

