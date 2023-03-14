

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
   clear_screen();
   write_string(15, "Hello world!");


}
