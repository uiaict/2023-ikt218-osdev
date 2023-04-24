#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Custom files
#include "include/descriptor_tables.h"
#include "include/terminal.h"
#include "include/interrupts.h"
#include "include/common.h"
#include "include/sc_to_ascii.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
   void kernel_main();
}

void kernel_main()
{
	// Initialize Global Descriptor Table
	init_gdt();

	// Initialize Interupt Descriptor Table
	init_idt();

	// Initialize Interupt Descriptor Table
	init_irq();

	// Initialize terminal and
	// and display a string.
    terminal_initialize();
    terminal_writestring("Hello, World!");

	// Create interrupt handlers for interrupt 3 and 4
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        terminal_writestring("Interrupt 3 - OK\n");
    }, NULL);

    register_interrupt_handler(4,[](registers_t* regs, void* context){
        terminal_writestring("Interrupt 4 - OK\n");
    }, NULL);


    // Trigger interrupts 3 and 4 which should call the respective handlers
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    // Disable interrupts temporarily
    asm volatile("sti");

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){
         // Read the scan code from keyboard
        unsigned char scan_code = inb(0x60);
        unsigned char ascii = scancode_to_ascii(scan_code);

        terminal_putchar(ascii);
        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

    // Print a message and enter an infinite loop to wait for interrupts
    terminal_writestring("Waiting...\n");
    while(1){};
    terminal_writestring("Done!...\n");
}


