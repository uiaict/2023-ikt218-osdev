#include "common.h"
#include "descriptor_tables.h"
#include "interrupts.h"
#include "keyboard.h"
#include "system.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    // Initialize Global Descriptor Table, Interrupt Descriptor Table and IRQ handlers
    init_gdt();
    init_idt();
    init_irq();

    // Implement three ISRs
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

    /*
    Trigger interrupt 3:
    asm volatile("int $0x3");
    */

    asm volatile("sti");

    // Implement ISR for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*)
    {
        uint8_t scancode = inb(0x60);                     // Read scancode from keyboard controller data port
        asm volatile("cli");

        const char* input = scancode_to_ascii(scancode);  // Translate scancode to ASCII 
        printf(input);                                    // Print ASCII character to screen 
    }, NULL);


    // Testing implementation of printf:
    /*printf("SYSTEM COMPROMISED.\n"
           "SHUTTING DOWN... SHUTTING DOWN... \tSHUTTING DOWN... SHUTTING DOWN... SHUTTI\tN\n"
           "G DOWN... SHUTTING DOWN... SHUTTING\t\t DOWN... SHUTTING DOWN... \n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n");*/

    while(1){};
}
