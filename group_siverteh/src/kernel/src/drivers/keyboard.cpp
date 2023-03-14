#include "keyboard.h"
#include "isr.h"
#include "ports.h"
#include "screen.h"

extern "C"
{
    #include "strings.h"
}

static int caps_lock = 0;
static int shift_pressed = 0;

//Lookup table for the keyboard. See scan codes defined in keyboard.h for indexes.
char scan_code_chars[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

//Function that gets the scancode of the key that was pressed.
static int get_scancode()
{
    //Initializes the variable scancode to 0.
    int scancode = 0;

    //Enters an infinite loop.
    while(1)
    {
        //Keeps checking if the keyboard has sendt a scancode by checking the first bit of the keyboard status port.
        if((inb(KEYBOARD_STATUS_PORT) & 1) != 0)
        {
            //When a scancode has been recieved it stores it in the scancode variable and exits the function.
            scancode = inb(KEYBOARD_DATA_PORT);
            break;
        }
    }

    //Returns the scancode.
    return scancode;
}

//Function that turns the keyboard characters into their alternate characters.
char alternate_chars(char ch) 
{
    switch(ch) {
        case '`': return '~';
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case '\\': return '|';
        case ';': return ':';
        case '\'': return '\"';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        default: return ch;
    }
}


static void keyboard_handler(registers_t regs) 
{
    //Sets up variables for the scancode and character.
    int scancode;
    char ch = 0;

    //Gets the scancode of the key that was pressed by calling the get_scancode function.
    scancode = get_scancode();

    //If the 0x80 bit is set in the scancode it means the key has been release and needs to be done.
    if(scancode & 0x80)
    {
        //Key release
    }
    //If not it means a key has been pressed and needs to be handled.
    else
    {
        //A switch statement based on the scancode occurs.
        switch(scancode)
        {   
            //If the caps lock key has been pressed:
            case SCAN_CODE_KEY_CAPS_LOCK:
                //If the caps lock is set to false set it to true.
                if(caps_lock == 0)
                {
                    caps_lock = 1;
                }
                //Else if the caps lock is set to true set it to false.
                else if(caps_lock == 1)
                {
                    caps_lock = 0;
                }
                break;

            //If the enter key is pressed print a new line.
            case SCAN_CODE_KEY_ENTER:
                printf("\n");
                break;
            
            //If the tab key is pressed print four spaces.
            case SCAN_CODE_KEY_TAB:
                printf("\t");
                break;
        
            //If the shift code is pressed
            case SCAN_CODE_KEY_LEFT_SHIFT:
                //If the shift_pressed is false set it to true.
                if(shift_pressed == 0)
                {
                    shift_pressed = 1;
                }
                //Else if the shift_pressed is true set it to false.
                else if(shift_pressed == 1)
                {
                    shift_pressed = 0;
                }
                break;
        
            //If the backspace key is pressed call the backspace function.
            case SCAN_CODE_KEY_BACKSPACE:
                backspace();
                break;

            //If the up key is pressed call the scroll_up function.
            case SCAN_CODE_KEY_UP:
                scroll_up();
                break;

            //If the down key is pressed call the scroll_down function.
            case SCAN_CODE_KEY_DOWN:
                scroll_down();
                break;
        
            //The default case.
            default:
                //Set the char
                ch = scan_code_chars[scancode];

                //If caps lock is on
                if(caps_lock)
                {
                    //And the shift key is pressed put it through the alternate_chars function.
                    if(shift_pressed)
                    {
                        ch = alternate_chars(ch);
                    }
                    //If only the caps lock is on turn the character into upper case.
                    else
                    {
                        ch = to_upper_char(ch);
                    }
                }
                //If the caps lock is not on.
                else
                {
                    //And the shift key is pressed
                    if(shift_pressed)
                    {
                        //And the character is in the alphabet
                        if(isalpha(ch))
                        {
                            //Turn it to uppercase.
                            ch = to_upper_char(ch);
                        }
                        else
                        {   
                            //Else run it through the alternate_chars function.
                            ch = alternate_chars(ch);
                        }
                    }
                }
            //Lastly print the character to the screen.    
            printf("%c", ch);
        }
    }
}
   
//Function to load the keyboard using the register_interrupt_handler function.
void load_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_handler);
}
