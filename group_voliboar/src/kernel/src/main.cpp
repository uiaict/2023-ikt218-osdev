#include "screen.h"

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
}
