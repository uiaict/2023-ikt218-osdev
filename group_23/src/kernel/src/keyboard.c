#include "../include/keyboard.h"
#include "../include/isr.h"
#include "../include/monitor.h"
#include "../include/common.h"

#define SC_MAX 57
#define BACKSPACE 0x0E
#define ENTER 0x1C
static char key_buffer[256];

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = inb(0x60);
    
    print_letter(scancode);


    
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
void print_letter(uint8_t scancode) 
{
    switch (scancode) 
    {
        case 0x0:
            monitor_write("ERROR");
            break;
        case 0x1:
            monitor_write("ESC");
            break;
        case 0x2:
            monitor_put('1');
            break;
        case 0x3:
            monitor_put('2');
            break;
        case 0x4:
            monitor_put('3');
            break;
        case 0x5:
            monitor_put('4');
            break;
        case 0x6:
            monitor_put('5');
            break;
        case 0x7:
            monitor_put('6');
            break;
        case 0x8:
            monitor_put('7');
            break;
        case 0x9:
            monitor_put('8');
            break;
        case 0x0A:
            monitor_put('9');
            break;
        case 0x0B:
            monitor_put('0');
            break;
        case 0x0C:
            monitor_put('-');
            break;
        case 0x0D:
            monitor_put('+');
            break;
        case 0x0E:
            monitor_write("Backspace");
            break;
        case 0x0F:
            monitor_write("Tab");
            break;
        case 0x10:
            monitor_put('Q');
            break;
        case 0x11:
            monitor_put('W');
            break;
        case 0x12:
            monitor_put('E');
            break;
        case 0x13:
            monitor_put('R');
            break;
        case 0x14:
            monitor_put('T');
            break;
        case 0x15:
            monitor_put('Y');
            break;
        case 0x16:
            monitor_put('U');
            break;
        case 0x17:
            monitor_put('I');
            break;
        case 0x18:
            monitor_put('O');
            break;
        case 0x19:
            monitor_put('P');
            break;
        case 0x1A:
            monitor_put('[');
            break;
        case 0x1B:
            monitor_put(']');
            break;
        case 0x1C:
            monitor_write("ENTER");
            break;
        case 0x1D:
            monitor_write("LCtrl");
            break;
        case 0x1E:
            monitor_put('A');
            break;
        case 0x1F:
            monitor_put('S');
            break;
        case 0x20:
            monitor_put('D');
            break;
        case 0x21:
            monitor_put('F');
            break;
        case 0x22:
            monitor_put('G');
            break;
        case 0x23:
            monitor_put('H');
            break;
        case 0x24:
            monitor_put('J');
            break;
        case 0x25:
            monitor_put('K');
            break;
        case 0x26:
            monitor_put('L');
            break;
        case 0x27:
            monitor_put(';');
            break;
        case 0x28:
            monitor_put('\'');
            break;
        case 0x29:
            monitor_put('`');
            break;
    }
}