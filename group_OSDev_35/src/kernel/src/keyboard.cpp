#include "keyboard.h"
#include "common.h"
#include "system.h"

char scan_code_chars[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0};

void keyboard_handler(registers_t *regs, void * /* context */)
{
    int status;
    int scancode = 0;
    char key = 0;

    while (1)
    {
        status = inb(0x64);
        if (status & 0x01)
        {
            scancode = inb(0x60);
            break;
        }

        if (scancode & 0x80)
            return;
    }

    //key = scan_code_chars[scancode];

    printf("%c", scan_code_chars[scancode]);
}