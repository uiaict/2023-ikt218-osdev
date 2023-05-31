extern "C" {

    #include "print.h"
}
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

/*void write_terminal(int colour, const char *string)
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}*/

void kernel_main()
{
    init_gdt();
    print_clear();
    print_str("Hello World");
}


