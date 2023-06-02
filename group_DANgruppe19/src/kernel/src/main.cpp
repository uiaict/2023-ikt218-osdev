#include "gdt.h"
#include "terminal.h"
#include "system.h"
#include "../interrupts/idt.h"
#include "../interrupts/isr.h"
#include "../interrupts/irq/irq.h"

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


void enable_interrupts() {
    asm volatile ("sti");
}

// Initialize the PS/2 keyboard
void init_keyboard() {
    // Disable devices
    outb(0x64, 0xAD);
    outb(0x64, 0xA7);

    // Flush output buffer
    while(inb(0x64) & 0x1) {
        inb(0x60);
    }

    // Enable first PS/2 port
    outb(0x64, 0xAE);

    // Enable scanning, but first check if keyboard is ready to receive a command
    //while(inb(0x64) & 0x2); // Wait until bit 1 of status register is 0
    //outb(0x60, 0xF4); // Send command to keyboard command port
}





void kernel_main()
{


init_gdt();
terminal_initialize();
remap_pic();
// Enable keyboard
//outb(0x60, 0xF4);
idt_init(); // Initialize the IDT for interrupt
init_keyboard();


scancode_to_ascii[0x1E] = 'a';
scancode_to_ascii[0x30] = 'b';
scancode_to_ascii[0x2E] = 'c';
scancode_to_ascii[0x20] = 'd';
scancode_to_ascii[0x12] = 'e';
scancode_to_ascii[0x21] = 'f';
scancode_to_ascii[0x22] = 'g';
scancode_to_ascii[0x23] = 'h';
scancode_to_ascii[0x17] = 'i';
scancode_to_ascii[0x24] = 'j';
scancode_to_ascii[0x25] = 'k';
scancode_to_ascii[0x26] = 'l';
scancode_to_ascii[0x32] = 'm';
scancode_to_ascii[0x31] = 'n';
scancode_to_ascii[0x18] = 'o';
scancode_to_ascii[0x19] = 'p';
scancode_to_ascii[0x10] = 'q';
scancode_to_ascii[0x13] = 'r';
scancode_to_ascii[0x1F] = 's';
scancode_to_ascii[0x14] = 't';
scancode_to_ascii[0x16] = 'u';
scancode_to_ascii[0x2F] = 'v';
scancode_to_ascii[0x11] = 'w';
scancode_to_ascii[0x2D] = 'x';
scancode_to_ascii[0x15] = 'y';
scancode_to_ascii[0x2C] = 'z';



terminal_write("Hello World!\n", 14);

terminal_write("Press a key...\n", 15);

enable_interrupts();

//asm volatile("int $0x21");

for (;;); // Infinite loop



// Manually trigger interrupts
    //asm volatile ("int $0");   // Divide by Zero Exception

    //asm volatile ("int $3");   // Software Breakpoint Exception

    //asm volatile ("int $4");   // User-defined Software Interrupt


    // To cause an invalid opcode exception, we can use the "ud2" instruction
    //asm volatile ("ud2");      // Invalid Opcode Exception

    // To cause a general protection fault, we can do an invalid memory access
    // Be aware that this will likely crash your OS, so you might not want to do this
    // without setting up a proper recovery mechanism
    //asm volatile ("mov %cr4, %eax");  // General Protection Fault


}
