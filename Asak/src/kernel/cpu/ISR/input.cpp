#include "cpu/input.h"

bool capsEnabled = false;

const char large_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '\016', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '\034', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};
const char small_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '\016', '?', 'q', 'w', 'e', 'r', 't', 'y',
                         'u', 'i', 'o', 'p', '[', ']', '\034', '?', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

char scancode_to_ascii(unsigned char* scan_code) {
    unsigned char a = *scan_code;
    if (a > 57) {
        switch (a)
        {
        case 58:      
            capsEnabled = !capsEnabled;
            break;
        case 72:    
            return -a;     
        case 75:   
            return -a;    
        case 77:    
            return -a;   
        case 80:     
            return -a; 
        case 170:      
            capsEnabled = !capsEnabled;
        default:
            break;
        }
        return 0;
    }

    if (a == 42) {
        capsEnabled = !capsEnabled;
    }

    int b = a;
    char c;
    if (capsEnabled) {
        c = large_ascii[b];
    }
    else {
        c = small_ascii[b];
    }
    return c;
}
