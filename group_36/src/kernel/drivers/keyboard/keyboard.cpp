#include "keyboard.h"


const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {
    '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '+', '\'', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', '\0', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', ':', '`', '\0', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '-', '\0', '*', '\0', ' ', '\0', // until 57 (F1)
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // F2-F9
    '\0', '\0', // F10, NumLock
    '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.' // Keypad
};

struct payload_t {
    keyboard_callback cb;
    void* ctx;
};
payload_t payload;

void UiAOS::IO::Keyboard::hook_keyboard(keyboard_callback a, void *b) {

    payload = {a, b};

    UiAOS::CPU::ISR::isr_t static_cb = [](UiAOS::CPU::ISR::registers_t *regs, void* cb_ptr){
        auto pay = (payload_t*)cb_ptr;
        uint8_t scancode = inb(0x60);
        if (scancode > SC_MAX) return;

        pay->cb(scancode, pay->ctx);

    };

    UiAOS::CPU::ISR::register_interrupt_handler(IRQ1, static_cb, &payload);
}

char UiAOS::IO::Keyboard::scancode_to_ascii(uint8_t scancode){
    return sc_ascii[(int) scancode];
}