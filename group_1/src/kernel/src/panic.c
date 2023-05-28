//This code is fetched from Perera

#include "panic.h"
void panic(const char *message, const char *file, uint32_t line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.


    // Halt by going into an infinite loop.
    for(;;);
}