#include <descriptor_tables.h>
#include <interrupts.h>


// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include <system.h>

    void kernel_main();
}


void kernel_main()
{
    printf("Hello World!\n");
    
    printf("Loading GDT\n");
    init_gdt();
    printf("GDT Loaded\n");

    printf("Loading IDT\n");
    init_idt();
    printf("IDT Loaded\n");
}
