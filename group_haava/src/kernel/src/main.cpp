#include "common.h"
#include "gdt.h"
#include "interrupts.h"
#include "system.h"
#include "vga.h"


#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main(unsigned long magic);
}

void kernel_main(unsigned long magic)
{
    vga_init();
    gdt_init();
    idt_init();
    irq_init();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Invalid magic number\n");
        return;
    }

    printf("Hello world\n");

    register_interrupt_handler(3,[](struct registers* regs){
        printf("Interrupt 3 - OK\n");
    });

    register_interrupt_handler(4,[](struct registers* regs){
        printf("Interrupt 4 - OK\n");
    });

    __asm__ __volatile__("int $0x3");
    __asm__ __volatile__("int $0x4");
    __asm__ __volatile__("int $0x7");

    register_irq_handler(IRQ1, [](struct registers*){
        // Print the scan code from keyboard
        vga_putchar((char)inb(0x60));

        // Disable interrupts temporarily
        asm volatile("cli");
    });

    // Print a message and enter an infinite loop to wait for interrupts
    printf("Waiting...\n");
    while(1){};
}
