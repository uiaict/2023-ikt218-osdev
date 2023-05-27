#include "keyboard.h"
// #include "system.h"
#include "interrupts.h"
#include "common.h"

extern "C"{
    #include "system.h"
}


// @brief Array of ascii characters for each scancode.
const int ascii_key_map[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '+', '\\', 0, 0, 
                            'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 0, 0, 0, 0, 
                            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, 0, 0, 0, 
                            'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, 0, 0,
                            ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/// @brief Function to register the keyboard interrupt handler.
void keyboard_handler()
{
    /// Register the IRQ1, keyboard, interrupt handler:
    register_irq_handler(IRQ1, [](registers_t* regs, void* data)
	{
        /// Read the scancode from the keyboard data buffer.
        uint8_t scancode = inb(0x60);

        /// Convert the scancode to an ascii character.
        char ascii = convert_to_ascii(scancode);
        /// Print the ascii character to the screen.
        printf("%c", ascii);
        //printf("%i ", scancode);
	}, NULL);
}

/// @brief Function to convert a scancode to an ascii character.
/// @param scancode The scancode to convert.
/// @return ascii character
char convert_to_ascii(uint8_t scancode)
{
    /// Create a static variable to keep track of the shift key (and capslock).
    static bool shift = false;
    /// Create a variable to hold the ascii character.
    char ascii = 0;

    /// Check if the scancode is a valid ascii character.
    /// If not do not print any character.
    if(scancode > 200)
        return 0;

    /// If the scancode is 28, print a new line.
    if(scancode == 28)
    {
        printf("\n");
        return 0;
    }

    /// If the delete button is pressed, clear the screen.
    if (scancode == 83)
    {
        clearScreen();
        printf("WELCOME TO UIA OS GROUP 7");
    }

    /// If the scancode is 42, this means shift is pressed down.
    /// Set the shift variable to true. This will be used to
    /// determine if the ascii character should be upper or lower case.
    if(scancode == 42)
    {
        shift = true;
        return 0;
    }
    /// If the scancode is 170, this means shift is released.
    /// Set the shift variable to false. This will be used to
    /// determine if the ascii character should be upper or lower case.
    if(scancode == 170)
    {
        shift = false;
        return 0;
    }
    /// If the scancode is 58, this means caps lock is pressed.
    /// Toggle the shift variable, which will be used to determine
    /// if the ascii character should be upper or lower case.
    if(scancode == 58)
        shift = !shift;
    
    /// If the shift variable is true, find the ascii character minus 32 to get the upper case character.
    if(shift)
    {
        char ascii = (char)ascii_key_map[scancode]-32;
        if(ascii < 0)
            return 0;
        return ascii;
    }
    /// If the shift variable is false, find the ascii character. It will be lower case.
    if(!shift)
    {
        char ascii = (char)ascii_key_map[scancode];
        return ascii;
    }
}