#include <cstdlib>
#include <cstdint>

#include "terminal.h"
#include "pit.h"

#define TEST_MEMORY false
#define TEST_INTERRUPT false

// This is defined in linker.ld
extern uint32_t end;

// Overload the new operator for single object allocation
void* operator new(std::size_t size) {
    // Call the C standard library function malloc()
    //to allocate memory of the given size and return a pointer to it
    return malloc(size);
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    // Call the C standard library function free()
    // to deallocate the memory pointed to by the given pointer
    free(ptr);
}

// Overload the new operator for array allocation
void* operator new[](std::size_t size) {
    // Call the C standard library function malloc()
    // to allocate memory of the given size and return a pointer to it
    return malloc(size);
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    // Call the C standard library function free()
    // to deallocate the memory pointed to by the given pointer
    free(ptr);
}

void operator delete(void* ptr, unsigned int) noexcept {
    free(ptr);
}

void operator delete[](void* ptr, unsigned int) noexcept {
    free(ptr);
}

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include <system.h>
    #include "memory.h"
    void kernel_main();
}

void kernel_main(){

    // Remove this 
    terminal_clear();

    // Initialize kernel memory manager with the end of the kernel image
    init_kernel_memory(&end);

    // Initialize Paging
    init_paging();

    // Setup PIT
    init_pit();
    
    // Print strating screen
    terminal_clear();
    terminal_print_title(true);
    printf("Hello World!\n");

    // Test memory
    if(TEST_MEMORY){
        terminal_newpage();
    
        // Allocate some memory using kernel memory manager
        void* memory1 = malloc(12345); 
        void* memory2 = malloc(54321); 
        void* memory3 = new char;
        char* memory4 = new char[1000]();

        print_memory_layout();

        delete memory1;
        delete memory2;
        delete memory3;
        delete memory4;

        print_memory_layout();
    }

    // Wait for interrupts
    while(1){
        
        // Test interrupts
        if(TEST_INTERRUPT){
            printf("Sleeping with interrupts...   ");
            sleep_interrupt(1000);
            printf("Finished sleeping\n");
            printf("Sleeping with busy-waiting... ");
            sleep_busy(1000);
            printf("Finished sleeping\n");
        }else{
            sleep_interrupt(1000);
        }
    };

}