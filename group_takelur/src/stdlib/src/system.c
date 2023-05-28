#include "system.h"

// simplified printf version that supports %d, %s, %c and %%
void printf(char *str, ...)
{
    char *arg = (char *) &str + sizeof(str);
    while (*str != '\0') {
        if (*str == '%') {
            switch (*++str) {
                case 'd':
                    print_int(*((int *) arg++));
                    break;
                case 's':
                    print_str(*((char **) arg++));
                    break;
                case 'c':
                    print_char(*((char *) arg++));
                    break;
                case '%':
                    print_char('%');
                    break;
            }
        } else {
            print_char(*str);
        }
        str++;
    }
}