#include <stdarg.h>

#include "system.h"
#include "vga.h"

/*
 * printf uses file format specification found in
 * The Open Group Base Specifications Issue 7, 2018 edition
 * section 5. File Format Notation.
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap05.html#tag_05
 */
int printf(const char *format, ...)
{
    va_list ap;
    char buf[256] = { '\0' };

    va_start(ap, format);
    size_t offset = 0;
    for (size_t i = 0; i < strlen(format); i++) {
        if (format[i] == '%') {
            switch (format[i + 1]) {
                case 's':
                    char* tmp_buf = va_arg(ap, char*);
                    for (size_t j = 0; j < strlen(tmp_buf); j++) {
                        buf[i + j] = tmp_buf[j];
                        offset++;
                    }
                    offset -= 2;    // Match the removed characters, with those added
                    i++;            // Skip the matched conversion specifier 's'.
                    break;
                case 'c':
                    buf[i] = (char)va_arg(ap, int);
                    offset--;   // Match the character removed, with the one added
                    i++;        // Skip the matched conversion specifier 'c'.
                    break;
                case 'd':
                    //int d = va_arg(ap, int);
                    // FIXME: Implement it
                    break;
                case 'x':
                case 'X':
                    //int x = va_arg(ap, int);
                    // FIXME: Implement it
                    break;
                default:
                    // Format specification that is not implemented, or does not
                    // exist.
                    break;
            }
        } else {
            buf[i + offset] = format[i];
        }
    }
    va_end(ap);
    vga_writestring(buf);
    return 0;
}
