#include "system.c"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    int fem = 5;
    char* ord = "helloworld!";
    size_t lengde = strlen(ord);
    int seks = 6;
}
