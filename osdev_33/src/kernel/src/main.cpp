
#include "system.h"
#include "screenstuff.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}




void kernel_main()
{
    clear_screen();

    int white = 15;
    const char* hei = "Hello World!";
    write_string(white, hei);

}
