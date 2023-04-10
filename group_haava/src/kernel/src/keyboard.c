#include "common.h"
#include "interrupts.h"
#include "keyboard.h"
#include "vga.h"

#define PS2_DATA    0x60 /** PS/2 controller data port - Read/Write */

#define BACKSPACE   0x0E
#define SC_MAX      57

const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '\n', '?', 'A', 'S', 'D',
                         'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?',
                         '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',
                         '?', '?', '?', ' '};

static void keyboard_callback()
{
    uint8_t scan_code = input_from_port(PS2_DATA);

    if (scan_code > SC_MAX)
        return;
    if (scan_code == BACKSPACE) {
        vga_backspace();
    } else {
        char letter = sc_ascii[(int)scan_code];
        char str[2] = {letter, '\0'};
        vga_writestring(str);
    }
}

void keyboard_init()
{
    register_irq_handler(IRQ1, keyboard_callback);
}
