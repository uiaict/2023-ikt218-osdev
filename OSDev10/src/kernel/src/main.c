#include "descriptor_tables.h"
#include "monitor.h"
#include "isr.h"
#include "keylogger.h"

extern u32int end; // This is defined in linker.ld

// Define entry point in asm to prevent C++ mangling
extern void kernel_main();


void kernel_main()
{
    init_descriptor_tables();

    monitor_clear();
    monitor_write("Welcome to OS10!\n");

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");

    asm volatile ("sti");

    init_keylogger();

    monitor_write("Starting keylogger...\n");
    while(1){};
    monitor_write("Goodbye");
}