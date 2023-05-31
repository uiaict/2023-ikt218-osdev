extern "C" {

    #include "print.h"
    #include "system.h"
}


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


void kernel_main()
{
    init_gdt();
    print_clear();
    print_str("Hello World");
    print_str("\n");
    print_str("NYYYY Linje");
}
