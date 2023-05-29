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

    asm volatile("sti");
    
    screenWrite("");

    //Interrupt for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){
        unsigned char scan_code = inb(0x60);
        const char character = ASCII_LT[scan_code];
        if (scan_code > 0) {
            screenWriteCharacter(character);
        }
    }, NULL);

    screenWrite("");
    screenWrite("Press between 1-9");
    while(1){};
}

