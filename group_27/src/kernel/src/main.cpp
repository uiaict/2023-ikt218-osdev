
#include "system.h"
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void test();
    int kernel_main();
}

void test()
{
    init_gdt();
}

int kernel_main()
{
    return 0xDEADBABA;
}
