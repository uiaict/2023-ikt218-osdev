
#include "system.h"
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void test();
    void kernel_main();
}

void test()
{
    init_gdt();
}

void kernel_main()
{

}
