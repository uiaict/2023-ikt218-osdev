

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

//extern void test_gdt();

void kernel_main()
{
   write_string(15, "Hello world!");
   //test_gdt();
}
