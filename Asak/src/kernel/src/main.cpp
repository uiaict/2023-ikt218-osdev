#include <cpu/isr.h>
#include <screen.h>
#include "system.c"


extern uint32_t end;
// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
    #include "kernel/memory.h"
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
    //Clearing the screen and printing welcome message in GDT
    print("print() implemented!\n");
    // Initialize memory
    memory_init(&end);

    // Register our handlers
    register_all_interrupt_handlers();
    register_all_irq_handlers();
  
    // Test the interrupts 
    //print("\nTriggering Interrupt 2: ");
    //__asm("int $0x2");
    //print("\nTriggering Interrupt 3: ");
    //__asm("int $0x3");

    print("\n\nWaiting for interrupts... *Cricket Noises*\n");
   
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();

    memory_print();

    while(1){};
}