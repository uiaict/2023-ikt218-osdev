// Written by Group 39 IKT218 Project Spring 2023.

#include "../screen/screen.h"

// This enables assembly code to call our kernel_main function. 
extern "C" {
    void kernel_main();
}


void dividebyzero()
{
    int a = 5/0; //This will cause a division by zero
}


void kernel_main()
{
    clearScreen(); // Clear screen before writing output



    dividebyzero();
    printString("Hello World"); // Write "Hello World" to the screen.
    int b = 55;
    int c = 76;
}

