#include "system.h"
#include "screen.h"
#include "idt.h"
#include "common.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{

   // Trigger created interrupts manually
    screenWrite("");
    asm volatile ("int $0x2");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    screenWrite("");
    screenWrite("HELLO WORLD!");

    screenWrite("Waiting...");
    while(1){};
    screenWrite("Done!...");
}

