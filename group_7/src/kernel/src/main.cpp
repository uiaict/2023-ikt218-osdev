#include "gdt.h"
#include "idt.h"
#include "interrupts.h"
#include <cstddef>
#include <stdint.h>
#include <cstdlib>
#include "common.h"
#include "keyboard.h"


extern uint32_t end; // This is defined in linker.ld


// Define entry point in asm to prevent C++ mangling
extern "C"{
    // Calls the kernel_main assembly function.
    #include "system.h"
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


void demonstrate_page_fault(){

    void (*callback)(registers_t&) = [](registers_t& regs)
    {
        // A page fault has occurred.
        // The faulting address is stored in the CR2 register.
        uint32_t faulting_address;
        asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

        // The error code gives us details of what happened.
        int present   = !(regs.err_code & 0x1); // Page not present
        int rw = regs.err_code & 0x2;           // Write operation?
        int us = regs.err_code & 0x4;           // Processor was in user-mode?
        int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
        int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

        // Output an error message.
        printf("Page fault! ( ");
        if (present) {printf("present ");}
        if (rw) {printf("read-only ");}
        if (us) {printf("user-mode ");}
        if (reserved) {printf("reserved ");}
        printf(") at 0x%x", faulting_address);
        printf("\n");
        // panic("Page fault");
    };

    // Create interrupt handler for interrupt 14, which is page fault
    register_interrupt_handler(14,[](registers_t* regs, void* context){
        void (*callback)(registers_t*) = reinterpret_cast<void (*)(registers_t*)>(context);
        callback(regs);

        printf("Page Fault!\n");
    }, (void*)callback);

    uint32_t *ptr = (uint32_t*)0xA0000000;
    uint32_t do_page_fault = *ptr;

}

/// @brief The kernel main function.
void kernel_main()
{

    // Clear the screen
    clearScreen();
 
     // Initialize kernel memory manager with the end of the kernel image
    init_kernel_memory(&end);

   
    
    // Initialize the global descriptor table:
    init_gdt();
    // Initialize the interrupt descriptor table:
    init_idt();

    init_irq();
 
    init_paging();
 
      // Print memory layout
    print_memory_layout();


    // Allocate some memory using kernel memory manager
    void* some_memory = malloc(12345);
    void* memory2 = malloc(54321);
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();
   

    // Initialize the interrupt service routines:
    
    // Register the ISR1 interrupt handler:
    demo_interrupts();
    
    // Register the IRQ1, keyboard, interrupt handler:
    keyboard_handler();

    // This will trigger the ISR1 interrupt:
    //asm volatile("int $0x01");
    
    asm volatile("sti");

    printf("WELCOME TO UIA OS! \nPress delete to clear screen..\n\n" );
    
    while (1){}
    
}
