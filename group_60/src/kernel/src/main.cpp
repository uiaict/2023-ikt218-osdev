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
    printf("IDT Loaded\n")

    register_interrupt_handler(3,[](registers_t* regs, void* context){
        printf("Interrupt 3 - OK\n");
    }, NULL);

    asm volatile ("int $0x3");

}
