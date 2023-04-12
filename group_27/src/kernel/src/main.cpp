
#include "printing.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}
 
// Code from https://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C

int i = 0;
 
void kernel_main(void) 
{
	clear_terminal();
    //print_logo();

	//asm volatile ("int $0x3");
	//asm volatile ("int $0x24");

	// Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){
		i++;
        write_int_to_terminal(5, i);

        // Read the scan code from keyboard
        unsigned char scan_code = inb(0x60);

        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

	asm volatile ("int $0x21");


    // Print a message and enter an infinite loop to wait for interrupts
    write_to_terminal(6, "Waiting...");
    while(1){};
}