#include "gdt.h"
#include "terminal.h"
#include "system.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


void kernel_main()
{
init_gdt();
terminal_initialize();
terminal_write("Hello World!", 12);
}
