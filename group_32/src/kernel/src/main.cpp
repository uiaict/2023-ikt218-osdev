
#include "system.h"
#include "../screen/screen.h"
#include "../src/gdt/gdt.h"
#include "../src/idt/idt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main() {
    /* Initialize terminal interface */
    screenInitialize();

    // Initialize Global Descriptor Table (GDT) and Interrupt Descriptor Table (IDT)
    init_gdt();
    init_idt();

	screenWrite("Hello World! ");
    while (1);
    screenWrite("Done! ");
}