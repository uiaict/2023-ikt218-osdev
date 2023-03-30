#include "system.h"
#include "gdt.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
    void init_descriptor_tables();
}

void kernel_main()
{
    printf("Hello");
    init_descriptor_tables();
    printf("gdt initialized");

    
}



