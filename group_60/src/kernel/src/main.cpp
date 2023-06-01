#include <descriptor_tables.h>

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include <system.h>
    
    void kernel_main();
}

void kernel_main()
{
    init_gdt();
    printf("Hello World!");
}