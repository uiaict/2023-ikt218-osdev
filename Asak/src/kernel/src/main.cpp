#include "system.c"
#include <screen.h>
#include "../cpu/ISR/isr.h"


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    //Clearing the screen and printing welcome message in GDT

    print("print() implemented!\n");

    // Register our interrupt_handlers
    register_all_interrupt_handlers();

    /* Test the interrupts */
    print("\nTriggering Interrupt 2: ");
    __asm("int $0x2");
    print("\nTriggering Interrupt 3: ");
    __asm("int $0x3");
}
