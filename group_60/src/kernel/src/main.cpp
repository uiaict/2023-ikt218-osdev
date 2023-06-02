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
    load_idt();
    printf("IDT Loaded")

    register_interrupt_handler(3,[](registers_t* regs, void* context){
        printf("Interrupt 3 - OK\n");
    }, NULL);

    asm volatile ("int $0x3");

}
