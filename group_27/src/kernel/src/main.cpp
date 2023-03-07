
#include "system.h"
#include "common.h"
#include "monitor.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    *(char*)0xb8000 = 'Y';
    *(char*)0xb8002 = 'O';
}