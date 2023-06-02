#include "keyboard.h"
#include "common.h"
#include "scancode_table.h"
#include "isr.h"
#include <stdbool.h>
#include "print.h"
#include "monitor.h"

// Keep track of the keyboard state
static char keyboard_buffer[KB_BUFFER_SIZE];
static unsigned int keyboard_buffer_head = 0;
static unsigned int keyboard_buffer_tail = 0;
static bool left_shift_pressed = false;
static bool right_shift_pressed = false;
static bool caps_lock_active = false;
static bool alt_gr_pressed = false;

char to_uppercase(char c);  // Function prototype for to_uppercase

void keyboard_processing(registers_t regs) 
{
    unsigned char scancode;

    scancode = inb(KB_PORT); // Reads from input port

    if (scancode & RELEASE) 
    {
        // KEY RELEASED
        if (scancode - RELEASE == SCANCODE_L_SHIFT || scancode - RELEASE == SCANCODE_R_SHIFT) 
        { 
            left_shift_pressed = false;
            right_shift_pressed = false;
        } else if (scancode - RELEASE == SCANCODE_R_ALT) 
        {
            alt_gr_pressed = false;
        }
    } else 
    {
        // KEY PRESSED
        if (scancode == SCANCODE_L_SHIFT || scancode == SCANCODE_R_SHIFT) 
        {
            left_shift_pressed = true;
            right_shift_pressed = true;
        } else if (scancode == SCANCODE_CAPS_LOCK) 
        {
            caps_lock_active = !caps_lock_active;
        } else if (scancode == SCANCODE_R_ALT) 
        {
            alt_gr_pressed = true;
        } else {
            char ascii = scancode_table[scancode];
            if ((left_shift_pressed || right_shift_pressed) != caps_lock_active) 
            {
                switch (ascii) // Adding a few special characters while holding shift
                {
                    case '1': ascii = '!'; break;
                    case '2': ascii = '\"'; break;
                    case '3': ascii = '#'; break;
                    case '5': ascii = '%'; break;
                    case '6': ascii = '&'; break;
                    case '7': ascii = '/'; break;
                    case '8': ascii = '('; break;
                    case '9': ascii = ')'; break;
                    case '0': ascii = '='; break;
                    case '+': ascii = '?'; break;
                    case '\'': ascii = '*'; break;
                    case '.': ascii = ':'; break;
                    case '-': ascii = '_'; break;
                    case ',': ascii = ';'; break;
                    default: ascii = to_uppercase(ascii); // Convert to uppercase for other characters
                }
            }

            if (alt_gr_pressed) 
            {
                switch (ascii) // Adding a few special characters while holding alt gr
                {
                    case '2': ascii = '@'; break;
                    case '3': ascii = '£'; break;
                    case '4': ascii = '$'; break;
                    case '7': ascii = '{'; break;
                    case '8': ascii = '['; break;
                    case '9': ascii = ']'; break;
                    case '0': ascii = '}'; break;
                    case '^': ascii = '~'; break;
                    case 'c': 
                    {
                        ascii = '\0';
                        clear_monitor(); 
                        keyboard_buffer_head = 0; 
                        keyboard_buffer_tail = 0; 
                        break;
                    }
                    default: break; // I do not modify other characters
                }
            }
        
        // Put the ASCII character in the buffer
        keyboard_buffer[keyboard_buffer_head] = ascii;

        // Increment buffer head pointer, wrap around if necessary
        keyboard_buffer_head = (keyboard_buffer_head + 1) % KB_BUFFER_SIZE;

        // If head and tail point to the same index there is an overflow. So I force the tail to advance, discarding the oldest entry
        if (keyboard_buffer_head == keyboard_buffer_tail) 
        {
            keyboard_buffer_tail = (keyboard_buffer_tail + 1) % KB_BUFFER_SIZE;
        }
        }
    }
}

// Read character from the buffer
char keyboard_read() 
{
    if (keyboard_buffer_head == keyboard_buffer_tail) 
    {
        return '\0';    // Return null to terminate string if buffer is empty
    }

    char c = keyboard_buffer[keyboard_buffer_tail];  // Get the next character from buffer

    keyboard_buffer_tail = (keyboard_buffer_tail + 1) % KB_BUFFER_SIZE;  // Increment the buffer tail pointer, wrap around if needed

    return c;
}

char to_uppercase(char c) 
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}
