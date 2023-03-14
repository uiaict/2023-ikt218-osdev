

// Define entry point in asm to prevent C++ mangling
extern "C"
{
#include "system.h"
    void kernel_main();
}

void kernel_main()
{
    clear_screen();
    //write_string(15, "Hello world!");
    unsigned int pos = 0;
    pos = printk(pos, "Hello, %s! The answer \n is %d.", "world", 42);
    pos = printk(pos, "%d", 696969420);
}