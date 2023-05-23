//
// Created by per on 1/3/23.
//
#include "exception.h"




void panic(const char *message, const char *file, uint32_t line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.


    // Halt by going into an infinite loop.
    for(;;);
}

void panic_assert(const char *file, uint32_t line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    // Halt by going into an infinite loop.
    for(;;);
}