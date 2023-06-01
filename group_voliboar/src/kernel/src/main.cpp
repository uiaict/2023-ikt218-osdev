#include "screen.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "gdt.h"
    void kernel_main();
}

void kernel_main()
{
    // Initialize the GDT and the IDT
    init_gdt();

    // Will clear the terminal
    terminal_initialize();
 
    // Will print the given string to the terminal
	terminal_writestring("Hello World");
}
