

// Define entry point in asm to prevent C++ mangling
extern "C"
{
#include "system.h"
    void kernel_main();
}

extern "C" void test_gdt();

void kernel_main()
{
    clear_screen();
    printk("Hello, %s! The answer \n\n is %d.", "world", 42);
    printk("%d", 696969420);
}