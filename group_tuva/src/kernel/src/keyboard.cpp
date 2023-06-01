#include "keyboard.h"
#include "common.h"
#include "hardware.h"


const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};



struct payload_t {
    keyboard_callback cb;
    void* ctx;
};
payload_t payload; // TODO add new and  delete etc.

void Keyboard::hook_keyboard(keyboard_callback a, void *b) {

    payload = {a, b};

    isr_t static_cb = [](registers_t *regs, void* cb_ptr){
        auto pay = (payload_t*)cb_ptr;
        uint8_t scancode = inb(0x60);
        if (scancode > SC_MAX) return; // Over SC_MAX is Release (I think)

        pay->cb(scancode, pay->ctx);

    };

    register_interrupt_handler(IRQ1, static_cb, &payload);
}

char Keyboard::scancode_to_ascii(uint8_t scancode){
    return sc_ascii[(int) scancode];
}