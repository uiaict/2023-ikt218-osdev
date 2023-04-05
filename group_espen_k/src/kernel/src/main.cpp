    #include "idt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main()
{
    clearTerminal();
    printf("Hello World");

    // Trigger some interrupts
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile ("int $0x5");



}
