#include "system.c"
#include "screen.h"
#include "screen.cpp"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    screen terminal;
    terminal.clear_screen();
    terminal.play_intro();
    terminal.print("print() implemented!\n");
    terminal.print("We can now call the print() function to get output\n");
}
