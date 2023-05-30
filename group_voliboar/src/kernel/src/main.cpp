

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
    terminal_initialize();
 
	terminal_writestring("Hello, kernel World!\n");
}
