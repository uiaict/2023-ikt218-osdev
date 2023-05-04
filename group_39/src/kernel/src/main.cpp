// Written by Group 39 IKT218 Project Spring 2023.

#include "../screen/screen.h"

// Define entry point in asm to prevent C++ mangling
extern "C" {
    void kernel_main();
}



void kernel_main()
{
    clearScreen(); // Clear screen before writing output
    printString("Hello World"); // Write "Hello World" to the screen.
}

