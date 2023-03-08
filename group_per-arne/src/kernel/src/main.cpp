
#include <libc/system.h>
#include "descriptor_tables.h"
#include "interrupts.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    init_gdt();
    init_idt();
    init_irq();

    // Create some interrupt handlers for 3
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        printf("Interrupt 3 - OK\n");
    }, NULL);

    // Create some interrupt handler for 4
    register_interrupt_handler(4,[](registers_t* regs, void* context){
        printf("Interrupt 4 - OK\n");
    }, NULL);


    // Fire interrupts! Should trigger callback above
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");



    // Disable interrutps
    asm volatile("sti");

    register_irq_handler(IRQ1, [](registers_t*, void*){
        printf("Yes we are going on!\n");
        unsigned char scan_code = inb(0x60); // Must read the code: https://wiki.osdev.org/I_Cant_Get_Interrupts_Working
        asm volatile("cli");
    }, NULL);


    printf("Waiting...\n");
    while(1){};
    printf("Done!...\n");
}
