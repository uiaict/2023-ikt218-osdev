// Written by Group 39 IKT218 Project Spring 2023.

#include "../screen/screen.h"

// This enables assembly code to call our kernel_main function. 
extern "C" {
    void kernel_main();
}


void kernel_main()
{
    clearScreen(); // Clear screen before writing output

    printString("Hello World"); // Write "Hello World" to the screen.
}

