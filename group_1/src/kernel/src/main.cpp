

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
    /**(char*)0xb8000 = 'O';
    *(char*)0xb8002 = 'l';
    *(char*)0xb8004 = 'e';*/

   write_string(15, "Hello world!");


}
