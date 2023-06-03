#include "descriptor_tables.h"
#include "print.h"
#include "isr.h"
#include "keylogger.h"
#include "timer.h"

extern u32int end; // This is defined in linker.ld

// Define entry point in asm to prevent C++ mangling
extern void kernel_main();


void kernel_main()
{
    init_descriptor_tables();

    clear_screen();
    print_string("Welcome to OS10!\n");

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");

    asm volatile ("sti");

    // Start tick tack timer.
    // tick tack every 10 seconds.
    init_ticktack(100);

    print_string("Starting timer running...\n");

    // Start keylogger.
    init_keylogger();

    print_string("Starting keylogger running...\n");
    while(1){};
    print_string("Goodbye");
}