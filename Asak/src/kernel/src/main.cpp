#include "system.c"
#include "screen.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    clear_screen();
    play_intro();
    print("print() implemented!\n");
    print("We can now call the print() function to get output\n");
}