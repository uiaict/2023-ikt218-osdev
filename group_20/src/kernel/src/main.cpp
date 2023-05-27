#include "system.h"
#include "screen.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    screenWrite("HELLO WORLD!");
}
