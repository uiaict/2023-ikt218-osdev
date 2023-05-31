#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Custom files
#include "include/descriptor_tables.h"
//#include "include/terminal.h"
#include "include/interrupts.h"
#include "include/common.h"
#include "include/sc_to_ascii.h"
#include "include/memory.h"
#include "include/pit.h"


extern uint32_t end;

// Define entry point in asm to prevent C++ mangling
extern "C"{
   void kernel_main();
}

// Overload the new operator for single object allocation
void* operator new(size_t size) {
    return custom_malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    custom_free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

// Overload the new operator for array allocation
void* operator new[](size_t size) {
    return custom_malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    custom_free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

void kernel_main()
{

    // Initialize terminal and
    terminal_initialize();

    // Initialize kernel memory manager with the end of the kernel image
    init_kernel_memory(&end);

	// Initialize Global Descriptor Table
	init_gdt();

	// Initialize Interupt Descriptor Table
	init_idt();

	// Initialize Interupt Descriptor Table
	init_irq();

    // Initialize Paging
    init_paging();
    
    // Print memory layout
    print_memory_layout();

    // Initialize PIT
    init_pit();

    // Enable interrupts temporarily
    asm volatile("sti");

    // Show that PIT works   
    uint16_t counter = 0;  
    while(true){
        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    };
      


    /*
    void* some_memory = custom_malloc(12345); 
    void* memory2 = custom_malloc(54321); 
    void* memory3 = custom_malloc(13331);
    char* memory4 = new char[1000]();
    */

	// Create interrupt handlers for interrupt 3 and 4
    /*
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        terminal_writestring("Interrupt 3 - OK\n");
    }, NULL);

    register_interrupt_handler(4,[](registers_t* regs, void* context){
        terminal_writestring("Interrupt 4 - OK\n");
    }, NULL);


    // Trigger interrupts 3 and 4 which should call the respective handlers
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");*/

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ0, [](registers_t*, void*) {
        printf("IRQ0 triggered!\n");

        send_EOI();
        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*) {
         // Read the scan code from keyboard
        unsigned char scan_code = inb(0x60);
        unsigned char ascii = scancode_to_ascii(scan_code);

        terminal_putchar(ascii);
        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

    // Print a message and enter an infinite loop to wait for interrupts
    // terminal_writestring("Waiting...\n");
    while(1){};
    terminal_writestring("Done!...\n");
}


