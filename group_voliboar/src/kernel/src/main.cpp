#include "screen.h"
#include "gdt.h"
#include "idt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    // Will clear the terminal
    terminal_initialize();
 
    // Will print the given string to the terminal
	terminal_writestring("Hello World");

    //triggers some inturupts to test if it works
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");
}
