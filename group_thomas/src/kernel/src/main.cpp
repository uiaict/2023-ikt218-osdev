#include "system.h"

void load_gdt(uint32_T);

// Define entry point in asm to prevent C++ mangling
extern "C" {
    void kernel_main();
}

void kernel_main()
{
    load_gdt();

}



