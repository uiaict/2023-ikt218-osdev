#include <descriptor_tables.h>

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include <system.h>

    void kernel_main();
}

void kernel_main()
{
    printf("Hello World!");
    
    printf("Loading GDT")
    init_gdt();
    printf("GDT Loaded")

    printf("Loading IDT")
    init_idt();
    printf("IDT Loaded")

    asm(”int 0x01”);

}
