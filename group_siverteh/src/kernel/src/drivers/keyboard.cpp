#include "keyboard.h"
#include "isr.h"
#include "ports.h"
#include "screen.h"

//Declare external C functions.
extern "C"
{
    #include "strings.h"
}

static int caps_lock = 0;
static int shift_pressed = 0;
static int altgr_pressed = 0;


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

//Function that turns the keyboard characters into their shift alternate characters.
char shift_alternate_chars(char ch) 
{
    switch(ch) {
        case '1': return '!';
        case '2': return '"';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '&';
        case '7': return '/';
        case '8': return '(';
        case '9': return ')';
        case '0': return '=';
        case '+': return '?';
        case '\\': return '`';
        case '\'': return '*';
        case '§': return '½';
        case 'å': return 'Å';
        case '¨': return '^';
        case 'æ': return 'Æ';
        case 'ø': return 'Ø';
        case '-': return '_';
        case ',': return ';';
        case '.': return ':';
        case '/': return '|';
        default: return to_upper_char(ch);
    }
}

//Function that turns the keyboard characters into their altgr alternate characters.
char altgr_alternate_chars(char ch)
{
    switch(ch) {
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '{';
        case '7': return '[';
        case '8': return ']';
        case '9': return '}';
        case '0': return '\\';
        case '+': return '~';
        case '<': return '|';
        case 'm': return 'µ';
        default: return ch;
    }
}

// The keyboard interrupt handler function
static void keyboard_handler(registers_t regs) 
{
    // Declare variables for the scancode and character
    int scancode;
    char ch = 0;

    // Get the scancode of the key that was pressed or released
    scancode = get_scancode();

    //Check if the 0x80 bit is set in the scancode (key release)
    if(scancode & 0x80)
    {
        //Remove the 0x80 bit from the scancode
        scancode &= ~0x80;

        // Check if the key being released is the Left Shift or Right Shift key
        if (scancode == SCAN_CODE_KEY_LEFT_SHIFT || scancode == SCAN_CODE_KEY_RIGHT_SHIFT)
        {
            //Set the shift_pressed variable to 0 (not pressed)
            shift_pressed = 0;
        }
        else if(scancode == SCAN_CODE_KEY_ALT)
        {
            //Set the altgr_pressed variable to 0 (not pressed)
            altgr_pressed = 0;
        }
    }
    //Else the action is a key press.
    else 
    {
        //Switch statement based on the scancode
        switch(scancode)
        {
            // If the Caps Lock key is pressed, toggle the caps_lock flag
            case SCAN_CODE_KEY_CAPS_LOCK:
                caps_lock = !caps_lock;
                break;

            // If the Enter key is pressed, print a new line
            case SCAN_CODE_KEY_ENTER:
                printf("\n");
                break;

            // If the Tab key is pressed, print a tab character
            case SCAN_CODE_KEY_TAB:
                printf("\t");
                break;

            // If the Left Shift or Right Shift key is pressed, set the shift_pressed variable to 1 (pressed)
            case SCAN_CODE_KEY_LEFT_SHIFT:
            case SCAN_CODE_KEY_RIGHT_SHIFT:
                shift_pressed = 1;
                break;

            case SCAN_CODE_KEY_ALT:
                altgr_pressed = 1;
                break;

            // If the Backspace key is pressed, call the backspace function
            case SCAN_CODE_KEY_BACKSPACE:
                backspace();
                break;

            // If the Up arrow key is pressed, call the scroll_up function
            case SCAN_CODE_KEY_UP:
                scroll_up();
                break;

            // If the Down arrow key is pressed, call the scroll_down function
            case SCAN_CODE_KEY_DOWN:
                scroll_down();
                break;

            // For all other keys
            default:
                // Get the corresponding character from the scan_code_chars table
                ch = scan_code_chars[scancode];

                // Handle the character based on the caps_lock and shift_pressed flags
                if(caps_lock)
                {
                    if(shift_pressed)
                    {
                        ch = shift_alternate_chars(ch);
                    }
                    else if(altgr_pressed)
                    {
                        ch = altgr_alternate_chars(ch);
                    }
                    else
                    {
                        ch = to_upper_char(ch);
                    }
                }
                else
                {
                    if(shift_pressed)
                    {
                        if(isalpha(ch))
                        {
                            ch = to_upper_char(ch);
                        }
                        else
                        {
                            ch = shift_alternate_chars(ch);
                        }
                    }
                    else if(altgr_pressed)
                    {
                        ch = altgr_alternate_chars(ch);
                    }
                }
                // Print the character to the screen
                printf("%c", ch);
        }
    }
}
   
//Function to load the keyboard using the register_interrupt_handler function.
void load_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_handler);
}
