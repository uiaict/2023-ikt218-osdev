
//#include "system.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

void kernel_main()
{
    write_string(13, "Halla");
}
