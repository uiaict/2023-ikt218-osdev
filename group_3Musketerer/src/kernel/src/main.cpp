extern "C" {

    #include "print.h"
}

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    print_clear();
    print_str("Hello World");
}
