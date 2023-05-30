// Define entry point in asm to prevent C++ mangling
extern "C" {
    #include "common.h"
    #include "system.h"
    #include "monitor.h"
    #include "gdt.h"
    #include "idt.h"
    #include "isr.h"
    #include "irq.h"
    #include "print.h"
    #include "interrupt_tests.h"
    #include "keyboard.h"
    #include "memory.h"
    #include "pit.h"
    void kernel_main();
}

// THE FOLLOWING FROM LINE 19 TO 39 ARE FROM ASSIGNMENT FILES:

extern uint32_t end; // This is defined in linker.ld
typedef uint32_t size_t;

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
    init_kernel_memory(&end);   // Initialize kernel memory
   
    init_gdt();                 // Initialize the GDT
    init_idt();                 // Initialize the IDT
    
    init_interrupt_handlers();  // Initialize interrupt handlers
    init_irq_handlers();        // Initialize IRQ handlers

    asm volatile("sti");        // Enable interrupts

    clear_monitor();

    /* PRINT TESTS */
    //printf("This should insert string: %s\n", "Hello World!");
    //printf("This should insert integer: %d\n", 12345);
    //printf("This should insert decimal %d as hex: %x\n", 1452, 1452);
    //printf("This should insert percentage char: %%\n");
    

    /* INTERRUPT TESTS
    I have not implementet any actual exception handling. My service routines only print information about which interrupt
    was triggered, and do not handle the fault. These tests therefore only triggers the ISR, and do not create an actual exception.
    */
    //printf("Triggering divide by zero exception...\n");
    //test_divide_by_zero();
    //printf("Triggering debug exception...\n"); 
    //trigger_debug_exception();
    //printf("Triggering breakpoint exception...\n");
    //trigger_breakpoint_exception();
    //printf("Triggering invalid opcode exception...\n");
    //trigger_invalid_opcode_exception();
    //printf("Triggering unhandled interrupt exception...\n");
    //trigger_unhandled_interrupt(); // Trigger interrupt 27, which only has the default handler I created and is not set explicitly

    /* MONITOR WRITING TESTS
    monitor_write("Welcome to OS version 0.0.001!\n", 0, 15);
    monitor_write("This should be on a new line\n\n", 0, 15);
    monitor_write("Does tabs work? : 1\t2\t3\t4\t5\n", 0, 15);
    monitor_write("Backspaces? : 1 \b2\b3 \b4\b5\n", 0, 15);
    monitor_write("BG colors? : ", 0, 15);
    monitor_write("RED ", 4, 15);
    monitor_write("GREEN ", 2, 15);
    monitor_write("BLUE \n", 1, 15);
    monitor_write("FG colors? : ", 0, 15);
    monitor_write("RED ", 0, 4);
    monitor_write("GREEN ", 0, 2);
    monitor_write("BLUE \n", 0, 1);
    monitor_write("\nWill now test scrolling, should get line 1-25...\n", 0, 15);
     Since no sleep function is implemented I will temporarily juse use a busy loop
    for (int i = 0; i < 1000000000; i++) {
        i = i + 1;
        i = i - 1;
    }
    monitor_write("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", 0, 15);
    */

   while(1)
   {
       char c = keyboard_read();
         if (c != 0)
              printf("%c", c);
   };
}