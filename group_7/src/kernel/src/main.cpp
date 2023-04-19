#include "gdt.h"
#include "idt.h"
#include "interrupts.h"
#include <cstddef>
#include <stdint.h>
#include <cstdlib>
#include "common.h"
// Define entry point in asm to prevent C++ mangling
extern "C"{
    // Calls the kernel_main assembly function.
    #include "system.h"

    void kernel_main();
}

void hook_keyboard()
{
    isr_t handler = [](registers_t* regs, void* data)
    {
        uint8_t scancode = inb(0x60);
        asm volatile("cli");
        printf("Is this working?\n");
        printf("Scancode: %i", scancode);
    };
    
    
    register_interrupt_handler(IRQ1, [](registers_t* regs, void* data)
    {
        uint8_t scancode = inb(0x60);
        asm volatile("cli");
        printf("Is this working?\n");
        printf("Triggered from the keyboard in teorie\n");
        //printf("Scancode: %i", scancode);
    }, NULL);

    printf("Keyboard hooked\n");
}

/// @brief The kernel main function.
void kernel_main()
{
    // Clear the screen
    clearScreen();
    
    
    // Initialize the global descriptor table:
    init_gdt();
    // Initialize the interrupt descriptor table:
    init_idt();

    init_irq();
    

    // Initialize the interrupt service routines:
    register_interrupt_handler(IRQ1, [](registers_t* regs, void* data)
    {
        uint8_t scancode = inb(0x60);
        asm volatile("cli");
        printf("Is this working?\n");
        printf("Scancode: %i", scancode);
    }, NULL);

    
    asm volatile("sti");
    
    printf("Hello World\n");

    while (1){}
    
}
