#include "gdt.h"
#include "terminal.h"
#include "system.h"
#include "../interrupts/idt.h"
#include "../interrupts/isr.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


void delay(int count) {
    volatile int temp;
    for (int i = 0; i < count * 100000; ++i) {
        temp = i;
    }
}




void kernel_main()
{
init_gdt();
terminal_initialize();
idt_init(); // Initialize the IDT for interrupt
terminal_write("Hello World!", 10);

test_output();

delay(100);
asm volatile ("int $0x20");
//asm volatile ("int $0x20");
delay(100);
/*
delay(1000); // Introduce a delay

    
    delay(1000); // Introduce a delay

    asm volatile ("int $0xC9");
    delay(1000); // Introduce a delay

    asm volatile ("int $0xCA");
    delay(1000); // Introduce a delay
*/


terminal_write("Hello World!\n", 10);

}
