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
    #include "../include/keyboard.h"

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
    

    init_descriptor_tables(); 
    init_paging();                    // Initialize paging
    monitor_clear();
    
    
    monitor_write("Hello, World!\n");
    

   
    //asm volatile ("int $0x3");
    //asm volatile ("int $0x4");
    
    asm volatile("sti");            // Enable interrupts
    
    init_keyboard();

    timer_phase(100);               // 100hz
    //init_timer();
    //sleeping_interrupts(10);         // Sleep for 5 seconds
    //sleeping_busy(5);               // Sleep for 5 seconds
    
    print_memory_layout();
    void* some_memory = malloc(12345);
    char* memory1 = new char[1000]();
    monitor_put('\n');
    monitor_write("memory layout after allocating");
    monitor_put('\n');

    print_memory_layout();
   
	
    while(1);
    
    
}