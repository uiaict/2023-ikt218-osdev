/*
* Code retrieved from https://github.com/perara/ikt218-advanced-operating-systems/blob/1ce6e0b734968ad952275b8bbff049b8b690c5fb/src/stdlib/stdlib/cpp/exception.h#L11
*/

#include "panic.h"
#include <stdint.h>


//This code is fetched from Perera


void panic(const char *message, const char *file, uint32_t line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.


    // Halt by going into an infinite loop.
    for(;;);
}