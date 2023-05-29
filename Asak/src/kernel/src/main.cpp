#include "system.c"
#include <screen.h>

extern uint32_t end;
// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    //Clearing the screen and printing welcome message in GDT
    //Wanted to see the "implemented" messages"

    print("print() implemented!\n");

    /* Test the interrupts */
    //print("\nSending IRQ: ");
    //__asm("int $0x2");
    //print("\nSending IRQ: ");
    //__asm("int $0x3");
}
