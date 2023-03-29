#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Custom files
#include "include/descriptor_tables.h"


// Define entry point in asm to prevent C++ mangling
extern "C"{
   void kernel_main();
}

void kernel_main()
{
	// Initialize Global Descriptor Table
	init_gdt();

	// Initialize terminal and
	// and display a string.
    terminal_initialize();
    terminal_writestring("Hello, World!");
}


