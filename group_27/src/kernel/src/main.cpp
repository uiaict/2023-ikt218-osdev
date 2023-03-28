
#include "system.h"
#include "gdt.h"
#include "idt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    printmyword("SHITBIOS (version 69)      ");
}
