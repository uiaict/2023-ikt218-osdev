#include <screen.h>
#include <util.h>
#include <ports.h>

/*
void keyboard_callback(registers_t regs) {
    // The PIC leaves us the scancode in port 0x60
    uint8_t scancode = port_byte_in(0x60);
    char *sc_ascii;
    int_to_ascii(scancode, sc_ascii);
    print("Keyboard scancode: ");
    print(sc_ascii);
    print(", ");
    print(scancode);
    print("\n");
}

// Initializes keyboard for IRQ1
void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
*/