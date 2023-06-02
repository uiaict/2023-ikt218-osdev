
#include "system.h"
#include "../screen/screen.h"
#include "../src/gdt/gdt.h"
#include "../src/idt/idt.h"
#include "interrupts.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void threeISR() {
    register_interrupt_handler(1,[](registers_t* regs, void* data){screenWrite("Interrupt 1 was triggered\n");},NULL);
    register_interrupt_handler(2,[](registers_t* regs, void* data){screenWrite("Interrupt 2 was triggered\n");},NULL);
    register_interrupt_handler(3,[](registers_t* regs, void* data){screenWrite("Interrupt 3 was triggered\n");},NULL);
}

void kernel_main() {
    /* Initialize terminal interface */
    screenInitialize();

    // Initialize Global Descriptor Table (GDT) and Interrupt Descriptor Table (IDT)
    init_gdt();
    init_idt();

    threeISR();
    // Trigger ISRs
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");
    asm volatile ("int $0x3");

    screenWrite("Hello World!\n");

    while (1);
    screenWrite("Done!\n");
}