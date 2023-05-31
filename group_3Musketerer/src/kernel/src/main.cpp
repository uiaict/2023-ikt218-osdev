#include "system.h"


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
    //write_terminal(11, "Hello WORLD"); //TODO: implement scroll/cursor (http://www.osdever.net/bkerndev/Docs/printing.htm)
}


