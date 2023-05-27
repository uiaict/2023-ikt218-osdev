
#include "system.h"
#include "test.h"

extern "C"{
    void kernel_main();
}

void kernel_main()
{
clearScreen();
write_string(0x0F, "Hello World!");
}

