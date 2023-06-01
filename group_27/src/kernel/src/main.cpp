#include "descriptor_tables.h"
#include "interrupts.h"
#include "common.h"
#include "keyboard.h"
#include "monitor.h"
#include "pit.h"
#include <cstdlib>
#include <song/song.h>
extern uint32_t end; // This is defined in linker.ld


// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include <libc/system.h>
    #include "memory.h"
    void kernel_main();
}

// Overload the new operator for single object allocation
void* operator new(std::size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

// Overload the new operator for array allocation
void* operator new[](std::size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

void kernel_main()
{
    // Initialize kernel memory manager with the end of the kernel image
    init_kernel_memory(&end); 

    // Initialize Global Descriptor Table (GDT)
    init_gdt();

    // Initialize Interrupt Descriptor Table (IDT)
    init_idt();

    // Initialize Interrupt Requests (IRQs)
    init_irq();

    // Initialize Interrupt Service Routines ( ISRs )
    init_isr();


    // Initialize Paging
    init_paging(); 
    // Print memory layout
    print_memory_layout();

    // Setup PIT
    init_pit();   

     // Allocate some memory using kernel memory manager
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();

    // Create interrupt handlers for interrupt 3 and 4
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        printf("Interrupt 3 - OK\n");
    }, NULL);

    register_interrupt_handler(4,[](registers_t* regs, void* context){
        printf("Interrupt 4 - OK\n");
    }, NULL);

    register_interrupt_handler(5,[](registers_t* regs, void* context){
        printf("Interrupt 5 - OK\n");
    }, NULL);

    // Trigger interrupts 3 and 4 which should call the respective handlers
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");


    // Enable interrupts temporarily
    asm volatile("sti");

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){
        //print("Yeah boiiii\n");

        // Read the scan code from keyboard
        unsigned char scan_code = inb(0x60);

        char c = scancode_to_ascii(&scan_code);

        if (c != 0) {
            char* d = &c;
            monitor_put(c, true);
        }

        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

    printf("Testing busy waiting...\n");
    sleep_busy(1000);
    printf("Busy waiting OK\n");
    printf("Testing waiting with interrupts...\n");
    sleep_interrupt(1000);
    printf("Interrupt sleep OK\n");

    // Print a message and enter an infinite loop to wait for interrupts
    printf("UIA OS is ready. Type \"help\" to see available commands");
    set_prefix("\n> ");
    while(1){
        // System runs in an infinite loop here
        // just doing its thing and waiting for interrupts
    };
}