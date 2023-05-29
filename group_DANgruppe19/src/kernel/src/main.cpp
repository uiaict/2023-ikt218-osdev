#include "gdt.h"
#include "terminal.h"
#include "system.h"
#include "../interrupts/idt.h"
#include "../interrupts/isr.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


void delay(int count) {
    volatile int temp;
    for (int i = 0; i < count * 100000; ++i) {
        temp = i;
    }
}




void kernel_main()
{
init_gdt();
terminal_initialize();
remap_pic();
idt_init(); // Initialize the IDT for interrupt
terminal_write("Hello World!\n", 14);



// Manually trigger interrupts
    asm volatile ("int $0");   // Divide by Zero Exception

    asm volatile ("int $3");   // Software Breakpoint Exception

    asm volatile ("int $4");   // User-defined Software Interrupt


    // To cause an invalid opcode exception, we can use the "ud2" instruction
    //asm volatile ("ud2");      // Invalid Opcode Exception

    // To cause a general protection fault, we can do an invalid memory access
    // Be aware that this will likely crash your OS, so you might not want to do this
    // without setting up a proper recovery mechanism
    //asm volatile ("mov %cr4, %eax");  // General Protection Fault


}
