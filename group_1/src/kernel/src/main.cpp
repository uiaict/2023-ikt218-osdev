extern "C"{
    #include "system.h"
    #include "gdt.h"
    #include "common.h"
    #include <stdlib.h>
    #include "paging.h"
    void kernel_main();
}

extern uint32_t end;
//extern "C" void test_gdt();


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
    clear_screen();
    init_descriptor_tables();
    
    
    printk("Hello, %s! The answer \n is %d.", "world", 42);
    printk("%d", 696969420);
    //asm volatile ("int $0x28");
    //asm volatile ("int $0x1");

    // Initialize Paging
    init_paging(); // <------ THIS IS PART OF THE ASSIGNMENT
    
    // Print memory layout
    //print_memory_layout(); // <------ THIS IS PART OF THE ASSIGNMENT
    
    // Setup PIT
    //init_pit(); // <------ THIS IS PART OF THE ASSIGNMENT
    
    // Allocate some memory using kernel memory manager
    // THIS IS PART OF THE ASSIGNMENT
void* some_memory = malloc(12345);
void* memory2 = malloc(54321);
void* memory3 = malloc(13331);
char* memory4 = new char[1000]();
}
