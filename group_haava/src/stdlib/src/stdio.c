#include <stdarg.h>

#include "system.h"
#include "vga.h"

static int print(const char *data, size_t length)
{
    const char *bytes = (const char *) data;
    for (size_t i = 0; i < length; i++)
        vga_putchar(bytes[i]);
    return 0;
}

/*
 * printf uses file format specification found in
 * The Open Group Base Specifications Issue 7, 2018 edition
 * section 5. File Format Notation.
 * https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap05.html#tag_05
 */
int printf(const char *format, ...)
{
    va_list ap;
    int written = 0;

    va_start(ap, format);
    while (*format != '\0') {
        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            print(format, amount);
            format += amount;
            written += (int) amount;
            continue;
        }

        const char *format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(ap, int);
            print(&c, sizeof(c));
        } else if (*format == 's') {
            format++;
            const char *str = va_arg(ap, const char*);
            size_t len = strlen(str);
            print(str, len);
            written += (int) len;
        } else if (*format == 'd') {
            format++;
            int num = va_arg(ap, int);
            char buffer[20];
            int i = 0;
            if (num == 0) {
                buffer[i++] = '0';
            } else if (num < 0) {
                buffer[i++] = '-';
                num = -num;
            }
            while (num != 0) {
                buffer[i++] = (char) (num % 10 + '0');
                num /= 10;
            }
            while (i > 0) {
                print(&buffer[--i], 1);
                written++;
            }
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            print(format, len);
            format += len;
            written += (int) len;
        }
    }
    va_end(ap);
    return written;
}
