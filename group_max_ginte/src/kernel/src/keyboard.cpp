#include "keyboard.h"

lookup_map lookup[] = {
    // Modified table from https://www.millisecond.com/support/docs/current/html/language/scancodes.htm
        {"1", "esc"},
        {"2", "1"},
        {"3", "2"},
        {"4", "3"},
        {"5", "4"},
        {"6", "5"},
        {"7", "6"},
        {"8", "7"},
        {"9", "8"},
        {"10", "9"},
        {"11", "0"},
        {"12", "-"},
        {"13", "="},
        {"14", "bs"},
        {"15", "\t"}, // Tab
        {"16", "Q"},
        {"17", "W"},
        {"18", "E"},
        {"19", "R"},
        {"20", "T"},
        {"21", "Y"},
        {"22", "U"},
        {"23", "I"},
        {"24", "O"},
        {"25", "P"},
        {"26", "["},
        {"27", "]"},
        {"28", "\n"}, // Enter
        {"29", "CTRL"},
        {"30", "A"},
        {"31", "S"},
        {"32", "D"},
        {"33", "F"},
        {"34", "G"},
        {"35", "H"},
        {"36", "J"},
        {"37", "K"},
        {"38", "L"},
        {"39", ";"},
        {"40", "'"},
        {"41", "`"},
        {"42", "LShift"},
        {"43", "\\"},
        {"44", "Z"},
        {"45", "X"},
        {"46", "C"},
        {"47", "V"},
        {"48", "B"},
        {"49", "N"},
        {"50", "M"},
        {"51", ","},
        {"52", "."},
        {"53", "/"},
        {"54", "RShift"},
        {"55", "PrtSc"},
        {"56", "Alt"},
        {"57", " "}, // Space
        {"58", "Caps"},
        {"59", "F1"},
        {"60", "F2"},
        {"61", "F3"},
        {"62", "F4"},
        {"63", "F5"},
        {"64", "F6"},
        {"65", "F7"},
        {"66", "F8"},
        {"67", "F9"},
        {"68", "F10"},
        {"69", "Num"},
        {"70", "Scroll"},
        {"71", "Home (7)"},
        {"72", "Up (8)"},
        {"73", "PgUp (9)"},
        {"74", "-"},
        {"75", "Left (4)"},
        {"76", "Center (5)"},
        {"77", "Right (6)"},
        {"78", "+"},
        {"79", "End (1)"},
        {"80", "Down (2)"},
        {"81", "PgDn (3)"},
        {"82", "Ins"},
        {"83", "Del"}
    };

const char* scancode_to_ascii(uint8_t scancode)
{
    /*
    * Scancode from keyboard controller data port is used as index into lookup table.
    * Current implementation just returns strings for names of non-printable ASCII characters.
    * Characters such as Tab and Enter are supported by printf.
    */
   
    if (scancode > SC_MAX)
    {
        return "";
    }

    // Scancodes start from 1
    int index = scancode - 1;

    const char* character = lookup[index].character;

    return character;
}
