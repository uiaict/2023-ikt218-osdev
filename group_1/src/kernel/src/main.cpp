
#include "system.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    *(char*)0xb8000 = 'O';
    *(char*)0xb8002 = 'l';
    *(char*)0xb8004 = 'e';

}
