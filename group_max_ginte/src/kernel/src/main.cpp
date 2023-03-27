#include "system.h"
#include "descriptor_tables.h"
#include "common.h"
#include "interrupts.h"
#include "keyboard.h"
//#include "scancodes.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    //printf("Hello World");
    init_gdt();
    init_idt();
    init_irq();
    //printf("\tHello World");


    register_interrupt_handler(1,[](registers_t* regs, void* context)
    {
        printf("Interrupt 1 triggered! \n");
    }, NULL);

    register_interrupt_handler(2,[](registers_t* regs, void* context)
    {
        printf("Interrupt 2 triggered! \n");
    }, NULL);

    register_interrupt_handler(3,[](registers_t* regs, void* context)
    {
        printf("Interrupt 3 triggered! \n");
    }, NULL);


    //asm volatile("int $0x3");

    asm volatile("sti");


    register_irq_handler(IRQ1, [](registers_t*, void*)
    {
        uint8_t scan_code = inb(0x60);
        asm volatile("cli");

        const char* key = ascii(scan_code);
        printf(key);
    }, NULL);

    //printf("        Hello World!");
    /*printf("SYSTEM COMPROMISED.\n"
           "SHUTTING DOWN... SHUTTING DOWN... \tSHUTTING DOWN... SHUTTING DOWN... SHUTTI\tN\n"
           "G DOWN... SHUTTING DOWN... SHUTTING\t\t DOWN... SHUTTING DOWN... \n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n");*/

  
    while(1){};
}
