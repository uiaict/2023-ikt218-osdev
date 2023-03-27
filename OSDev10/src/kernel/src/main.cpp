
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
    // Initialize gdt
    init_gdt();
    
    clear_screen();
    //print 
    printf("Hello World!");
    
}