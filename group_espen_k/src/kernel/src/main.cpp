#include <cstdlib>
#include <cstdint>
#include "terminal.h"
#include "pit.h"


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
    #include <system.h>
    #include "memory.h"
    void kernel_main();
}

void kernel_main()
{

    terminal_clear();
    terminal_write("Hello World");

    // Initialize kernel memory manager with the end of the kernel image
    init_kernel_memory(&end);

    // Initialize Paging
    init_paging();


    // Print memory layout
    print_memory_layout();

    init_pit();


/*     // Allocate some memory using kernel memory manager
    void* some_memory = malloc(12345); 
    //void* memory2 = malloc(54321); 
    //void* memory3 = malloc(13331);
    char* memory4 = new char[1000](); */

    // Trigger some interrupts
/*     asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5"); */

    // Print a message and enter an infinite loop to wait for interrupts
    terminal_write("Waiting...");
    while(1){};
    terminal_write("Done!...");

}
