#include "keyboard.h"
#include "common.h"
#include "system.h"

// Array for non-shifted characters
char scan_code_chars_lower[128] = {
    '\0', 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0',
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', '*', '\0', ' ',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
};

// Array for shifted characters
char scan_code_chars_upper[128] = {
    '\0', 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', '\0',
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0', '*', '\0', ' ',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
};



// Variable to keep track of whether the shift key is currently pressed
int shift_pressed = 0;


void keyboard_handler(registers_t *regs, void * /* context */)
{
    int status;
    int scancode = 0;
    while (1)
    {
        status = inb(0x64);
        if (status & 0x01)
        {
            scancode = inb(0x60);

            // Check if this is a key press or release
            int key_release = scancode & 0x80;
            
            // Normalize the scancode
            scancode &= ~0x80;

            // If this is a shift key, update the shift_pressed variable
            if (scancode == 0x2A || scancode == 0x36) // 0x2A and 0x36 are left and right shift
            {
                shift_pressed = !key_release;
                continue;
            }

            // If this is a key release, ignore it
            if (key_release)
                return;

            if (shift_pressed)
                printf("%c", scan_code_chars_upper[scancode]);
            else
                printf("%c", scan_code_chars_lower[scancode]);

            break;
        }
    }
}


void init_keyboard()
{
    register_interrupt_handler(33, keyboard_handler, NULL);
    
    /*
        Enable the IRQ1, then enable the hardware interrupts
        when using only 'asm volatile("int $0x21")' the program reads only one key press
        when using only 'asm volatile("sti")' the program reads nothing
        when using both the program functions as intended and reading the interrupts as long as the program runs.
    */
    asm volatile("int $0x21");
    asm volatile("sti");
}