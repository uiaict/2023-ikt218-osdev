#include "system.c"
#include <screen.h>


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    //Clearing the screen and printing welcome message in GDT
    //Wanted to see the "implemented" messages"

    print("print() implemented!\n");
    print("Sending IRQ");

    /* Test the interrupts */
    __asm("int $0x1");
}
