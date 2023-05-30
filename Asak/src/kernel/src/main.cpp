#include <screen.h>
#include "system.c"
#include "mem.h"

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
    printf("Test!\n");

    // Initialize memory
    mm_init(end);
    /* Test the interrupts */
    //print("\nSending IRQ: ");
    //__asm("int $0x2");
    //print("\nSending IRQ: ");
    //__asm("int $0x3");
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();
}
