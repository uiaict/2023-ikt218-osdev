#include "screen.h"
#include "ports.h"
#include <stdarg.h>
#include <stddef.h> 
#include <limits.h>
#include <system.h>

// Prints every char on the terminal
int putchar(int i) {
    char c = (char) i;
    print_char(c, -1, -1, WAKE_UP_NEO);
	return i;
}

// Bool print, necessary for printf down below
static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == -1)
			return false;
	return true;
}


void print_at(char *message, int col, int row) {
/* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WAKE_UP_NEO);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

/* Print a char on the screen at col , row , or at cursor position */
int print_char(char character, int col, int row, char attribute_byte)
{
     unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attribute_byte) {
        attribute_byte = WAKE_UP_NEO;
    } 

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = WAKE_UP_NEO;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (character == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = character;
        vidmem[offset+1] = attribute_byte;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy(get_offset(0, i) + (char*)VIDEO_ADDRESS,
                        get_offset(0, i-1) + (char*)VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = get_offset(0, MAX_ROWS-1) + (char*)VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_screen_offset(int col, int row)
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

int get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char*)VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WAKE_UP_NEO;
    }
    set_cursor_offset(get_offset(0, 0));
}

/* Copy bytes from one place to another . */
void memory_copy(char *source, char *dest, int no_bytes)
{
    int i;
    for (i = 0; i < no_bytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

// Standard printing function without formatting
void print(char *message) {
    print_at(message, -1, -1);
}

// Printf for formatting purposes
int printf(const char* __restrict__ format, ...) {
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




void panic(const char* format, ...) {
    printf("***KERNEL PANIC*** in %s at line %d in function: %s\n", __FILE__, __LINE__, __func__); 
    asm volatile("cli");
    for(;;);
    }

void play_intro()
{
    // Intro to our OS
    print("      [.                        [..         [....       [.. ..       \n");
    print("     [. ..                      [..       [..    [..  [..    [..     \n");
    print("    [.  [..     [....    [..    [..  [..[..        [.. [..           \n");
    print("   [..   [..   [..     [..  [.. [.. [.. [..        [..   [..         \n");
    print("  [...... [..    [... [..   [.. [.[..   [..        [..      [..      \n");
    print(" [..       [..     [..[..   [.. [.. [..   [..     [.. [..    [..     \n");
    print("[..         [..[.. [..  [.. [...[..  [..    [....       [.. ..       \n");
    print("----------------------------------------------------------------\n\n");
    print("--------------------------Hello World!--------------------------\n\n");

    // Til slutt må vi sette cursor til under beskjeden
    set_cursor_offset(get_offset(0, 13));
}

int get_offset(int col, int row) { 
    return 2 * (row * MAX_COLS + col); 
    }
int get_offset_row(int offset) { 
    return offset / (2 * MAX_COLS); 
    }
int get_offset_col(int offset) { 
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; 
    }
