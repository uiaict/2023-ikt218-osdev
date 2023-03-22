#include "libc/system.h"
#include <stdarg.h>
#include <limits.h>

extern void monitor_put(char c);


int putchar(int ic) {
    char c = (char) ic;
    monitor_put(c);
	return ic;
}

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}
 
int printf(const char* __restrict__ format, ...) {
    // TODO %d and alot of formatting is missing!
    // This you can implement yourtself!
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
 
	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;
 
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd') {
            format++;
            int num = va_arg(parameters, int);
            char buffer[20];
            int i = 0;
            if (num == 0) {
                buffer[i++] = '0';
            } else if (num < 0) {
                buffer[i++] = '-';
                num = -num;
            }
            while (num != 0) {
                buffer[i++] = num % 10 + '0';
                num /= 10;
            }
            while (i > 0) {
                if (maxrem < 1) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(&buffer[--i], 1))
                    return -1;
                written++;
            }
        } else if (*format == 'x') {
            format++;
            unsigned int num = va_arg(parameters, unsigned int);
            char buffer[20];
            int i = 0;
            if (num == 0) {
                buffer[i++] = '0';
            }
            while (num != 0) {
                int rem = num % 16;
                if (rem < 10) {
                    buffer[i++] = rem + '0';
                } else {
                    buffer[i++] = rem - 10 + 'a';
                }
                num /= 16;
            }
            while (i > 0) {
                if (maxrem    < 1) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&buffer[--i], 1))
                return -1;
            written++;
			}

		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}
 
	va_end(parameters);
	return written;
}