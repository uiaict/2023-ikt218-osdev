#include "common.h"
#include "descriptor_tables.h"
#include "interrupts.h"
#include "keyboard.h"
#include "pit.h"
#include <cstdlib>

extern uint32_t end;

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "memory.h"
    #include "system.h"
    void kernel_main();
}


// Overload the new operator for single object allocation
void* operator new(std::size_t size) {
    return malloc(size); // Call the C standard library function malloc() to allocate memory of the given size and return a pointer
}
// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    free(ptr); // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}
// Overload the new operator for array allocation
void* operator new[](std::size_t size) {
    return malloc(size); // Call the C standard library function malloc() to allocate memory of the given size and return a pointer
}
// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    free(ptr); // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}


void kernel_main()
{
    // Initialize the kernel memory manager
    init_kernel_memory(&end);

    // Print the memory layout
    print_memory_layout();

    // Initialize Global Descriptor Table, Interrupt Descriptor Table and IRQ handlers
    init_gdt();
    init_idt();
    init_irq();

    // Initialize paging
    init_paging();

    // Setup the PIT 
    init_pit();


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


    // Implement ISR for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*)
    {
        uint8_t scancode = inb(0x60);                     // Read scancode from keyboard controller data port
        asm volatile("cli");

        const char* input = scancode_to_ascii(scancode);  // Translate scancode to ASCII 
        printf(input);                                    // Print ASCII character to screen 
    }, NULL);

    // Set the interrupt flag to enable interrupts
    asm volatile("sti");


    // Testing implementation of printf:
    /*printf("SYSTEM COMPROMISED.\n"
           "SHUTTING DOWN... SHUTTING DOWN... \tSHUTTING DOWN... SHUTTING DOWN... SHUTTI\tN\n"
           "G DOWN... SHUTTING DOWN... SHUTTING\t\t DOWN... SHUTTING DOWN... \n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n"
           "SHUTTING DOWN...\n");*/
    

    // Verify memory managment 
    void* memory1 = malloc(1001);
    int* memory2 = new int(2002);
    delete(memory1);
    char* memory3 = new char[3000]();


    // Verify the PIT
    while(1){
        //printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        printf("[!]: Sleeping with busy-waiting (HIGH CPU).\n");
        sleep_busy(1000);
        //printf("[%d]: Slept using busy-waiting.\n", counter++);
        printf("[!]: Slept using busy-waiting.\n\n");
        //printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        printf("[!]: Sleeping with interrupts (LOW CPU).\n");
        sleep_interrupt(1000);
        //printf("[%d]: Slept using interrupts.\n", counter++);
        printf("[!]: Slept using interrupts.\n\n");
    };
}
