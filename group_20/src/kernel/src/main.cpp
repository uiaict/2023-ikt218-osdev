#include <cstdlib>
#include <cstdint>
#include "idt.h"
#include "gdt.h"
#include "common.h"

extern uint32_t end; // This is defined in linker.ld

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

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "memoryManagement.h"
    #include "screen.h"
    void kernel_main();
}

void kernel_main()
{
    //Initialization 
    init_kernel_memory(&end);
    start_gdt();
    start_idt();
    init_paging();

   // Trigger created interrupts manually
    screenWrite("");
    screenWrite("");
    asm volatile ("int $0x2");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    screenWrite("");
    screenWrite("HELLO WORLD!");

    asm volatile("sti");
    
    screenWrite("");

    //Interrupt for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){
        unsigned char scan_code = inb(0x60);
        const char character = ASCII_LT[scan_code];
        if (scan_code > 0) {
            screenWriteCharacter(character);
        }
        // Disable interrupts temporarily
        asm volatile("cli");
    }, NULL);

    
    // Allocate some memory using kernel memory manager
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();

    screenWrite("");
    screenWrite("Press between 1-9");


    while(1){};
}

