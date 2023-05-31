#include "descriptor_tables.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

extern void init_gdt();
extern void init_idt();


void kernel_main()
{
    terminal_setcolor(VGA_COLOR_WHITE);
    terminal_writestring("Hello World!\n");
    init_gdt();
    init_idt();
    terminal_writestring("Initializing GDT\n");
    terminal_writestring("Initializing IDT\n");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
}
