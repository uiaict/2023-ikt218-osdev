#include "terminal.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
    terminal_clear();
    terminal_write("Hello World");
    // Trigger some interrupts
/*     asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5"); */

    // Print a message and enter an infinite loop to wait for interrupts
    terminal_write("Waiting...");
    while(1){};
    terminal_write("Done!...");

}
