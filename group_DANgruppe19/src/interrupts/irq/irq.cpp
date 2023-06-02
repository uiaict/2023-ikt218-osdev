#include "irq.h"
#include "../../kernel/include/terminal.h"
#include "../idt.h"
#include <cstring>
#include <cstdio>

char scancode_to_ascii[128] = {0};

void print_scancode(unsigned char scancode) {
    for (int i = 7; i >= 0; --i) {
        char c = (scancode & (1 << i)) ? '1' : '0';
        terminal_write(&c, 1);
    }
    char newline = '\n';
    terminal_write(&newline, 1);
}




extern "C" {
    void irq0() {
        terminal_write("IRQ0 triggered!\n", 16);
        // handle IRQ0 here
        outb(0x20, 0x20);

        terminal_write("This will not show\n", 20);

    }
    /*void irq1() {
    terminal_write("IRQ1 triggered!\n", 16);
    // handle IRQ1 here
    outb(0x20, 0x20);
}*/
    void irq1() {

        if (inb(0x64) & 0x1) {
    
        terminal_write("Triggered IRQ1", 15);

        // Read a byte from the keyboard's data buffer
        unsigned char scancode = inb(0x60);

        // Print the scancode
        print_scancode(scancode);
    
        // Translate the scancode to ASCII using the lookup table
        if (scancode < 128) { // we only handle "key down" events in this simple example
            char ascii = scancode_to_ascii[scancode];

            if (ascii != 0) { // Check if ASCII value is non-zero
                    terminal_write(&ascii, 1);
                }
        } else { // "key up" event
        terminal_write("Virker fortsatt ikke", 21);
    }

        // Send end of interrupt (EOI) to the master PIC
        outb(0x20, 0x20);

        print_scancode(scancode);
        } 
    }
    void irq2() {
        terminal_write("IRQ2 triggered!\n", 16);
        // handle IRQ0 here
    }

    void irq3() {
        terminal_write("IRQ3 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq4() {
        terminal_write("IRQ4 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq5() {
        terminal_write("IRQ5 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq6() {
        terminal_write("IRQ6 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq7() {
        terminal_write("IRQ7 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq8() {
        terminal_write("IRQ8 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq9() {
        terminal_write("IRQ9 triggered!\n", 16);
        // handle IRQ0 here
    }
    void irq10() {
        terminal_write("IRQ10 triggered!\n", 17);
        // handle IRQ0 here
    }
    void irq11() {
        terminal_write("IRQ11 triggered!\n", 17);
        // handle IRQ0 here
    }
    void irq12() {
        terminal_write("IRQ12 triggered!\n", 17);
        // handle IRQ0 here
    }
    void irq13() {
        terminal_write("IRQ13 triggered!\n", 17);
        // handle IRQ0 here
    }
    void irq14() {
        terminal_write("IRQ14 triggered!\n", 17);
        // handle IRQ0 here
    }
    void irq15() {
        terminal_write("IRQ15 triggered!\n", 17);
        // handle IRQ15 here
    }
}




