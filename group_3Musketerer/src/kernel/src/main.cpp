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
    init_idt();
    print_clear();
    print_str("Welcome to group 22 osdev");
    print_str("\n");
    print_str("Hello World");
}
