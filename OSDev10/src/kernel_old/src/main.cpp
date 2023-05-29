
#include "gdt.h"
#include "interrupts.h"
#include "common.h"
#include "cstdlib"
extern uint32_t end; // This is defined in linker.ld

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
    // Initialize gdt
    init_gdt();
    init_idt();
    init_irq();

   


    clear_screen();
    
    //print 
    printf("Hello World!");

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile("sti");

   
   
    
}