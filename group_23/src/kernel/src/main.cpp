extern "C"{
    #include "system.h"
    #include <stddef.h>
    #include "../include/descriptor_tables.h"
    #include "../include/common.h"
    #include "../include/monitor.h"
    #include "../include/isr.h"
    #include "../include/heap.h"
    #include "../include/pit.h"
    #include "../include/paging.h"

}

extern uint32_t end; //defined in linker script




// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

// Overload the new operator for single object allocation
void* operator new(size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}


// Overload the new operator for array allocation
void* operator new[](size_t size) {
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept {
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}




void kernel_main()
{
    init_kernel_memory(&end);         // Initialize kernel memory

    monitor_clear();
    
    init_descriptor_tables();         // Initialize descriptor tables GDT and IDT
    monitor_write("Hello, World!\n");
   

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

     init_paging();
     print_memory_layout();

    asm volatile("sti");
    // Setup PIT
    init_timer(50); 
    
   
    

    
    
    //clear_screen();
    //write_string("Hello, World!");
	
    
    while(1);
    
}