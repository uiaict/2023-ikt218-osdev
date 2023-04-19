#include "descriptor_tables.h"
#include "interrupts.h"
#include "common.h"
#include <cstdlib>
extern uint32_t end; // This is defined in linker.ld


// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include <libc/system.h>
    void kernel_main();
}

void kernel_main()
{
    // Initialize Global Descriptor Table (GDT)
    init_gdt();

    // Initialize Interrupt Descriptor Table (IDT)
    init_idt();

    // Initialize Interrupt Requests (IRQs)
    init_irq();


    // Create interrupt handlers for interrupt 3 and 4
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        printf("Interrupt 3 - OK\n");
    }, NULL);

    register_interrupt_handler(4,[](registers_t* regs, void* context){
        printf("Interrupt 4 - OK\n");
    }, NULL);

    register_interrupt_handler(13,[](registers_t* regs, void* context){
        printf("Interrupt 13 - SHIIT\n");
    }, NULL);


    // Trigger interrupts 3 and 4 which should call the respective handlers
    //asm volatile ("int $0x3");
    //asm volatile ("int $0x4");

    // Enable interrupts temporarily
    asm volatile("sti");

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){
        printf("Yeah boiiii\n");

        // Read the scan code from keyboard
        unsigned char scan_code = inb(0x60);

        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

    asm volatile ("int $0x21");

    // Print a message and enter an infinite loop to wait for interrupts
    printf("Waiting...\n");
    while(1){};
    printf("Done!...\n");
}