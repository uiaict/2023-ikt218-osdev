
#include "system.h"

//#include "gdt.h"
//#include "gdt.cpp"

//#include 
// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
int a = 2;


a = a + 2;

}
