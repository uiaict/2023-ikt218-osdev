#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    // Calls the kernel_main assembly function.
    #include "system.h"

    void kernel_main();
}


/// @brief The kernel main function.
void kernel_main()
{
    // Initialize the global descriptor table:
    init_gdt();
   
    
    clearScreen();
    printf("Hello World");
}