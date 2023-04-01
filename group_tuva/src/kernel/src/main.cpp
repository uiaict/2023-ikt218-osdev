#include "system.h"
#include "gdt.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
    void init_descriptor_tables();
}

// Main entry point for kernel
void kernel_main()
{
    printf("Hello");

    // Initializes the descriptor tables, and prints to indicate
    // that the GDT has been successfully initialized
    init_descriptor_tables();
    printf("gdt initialized");

    
}



