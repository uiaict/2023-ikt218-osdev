#pragma once

#include <stdint.h>
#include <time.h>
#include <stdio.h>

    enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer; 
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
       ++terminal_row;
       }
       else if(c == '\n')
        {
            terminal_row = terminal_row + 1;
            terminal_column = 0;
        }
       if(terminal_row==VGA_HEIGHT){
           terminal_row=0;
        }
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_writedecimal(int num) {
    // Buffer to hold the string representation of the decimal number
    char buffer[20]; // Adjust the size as needed

    // Handle negative numbers
    if (num < 0) {
        terminal_putchar('-');
        num = -num;
    }

    // Convert the decimal number to a string
    int index = 0;
    while (num > 0) {
        buffer[index++] = '0' + (num % 10);
        num /= 10;
    }

    // Special case for zero
    if (index == 0) {
        buffer[index++] = '0';
    }

    // Reverse the string
    for (int i = index - 1; i >= 0; i--) {
        terminal_putchar(buffer[i]);
    }
}



    int isalnum(int c);
    int iscntrl(int c);
    int isgraph(int c);
    int islower(int c);
    int isprint(int c);
    int ispunct(int c);
    int isupper(int c);
    int isxdigit(int c);
    __attribute__((noreturn)) void abort();
    double acos(double x);
    double asin(double x);
    double atan2(double y, double x);
    double ceil(double x);
    void clearerr(FILE *stream);
    clock_t clock();
    double cos(double x);
    double cosh(double x);
    double difftime(time_t t1, time_t t2);
    void exit(int status);
    double exp(double x);
    int fclose(FILE *stream);
    int feof(FILE *stream);
    int ferror(FILE *stream);
    int fflush(FILE *stream);
    char *fgets(char *s, int size, FILE *stream);
    double floor(double x);
    double fmod(double x, double y);
    FILE *fopen(const char *path, const char *mode);
    int fprintf(FILE *stream, const char *format, ...);
    int fputs(const char *s, FILE *stream);
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    FILE *freopen(const char *path, const char *mode, FILE *stream);
    double frexp(double x, int *exp);
    int fseek(FILE *stream, long offset, int whence);
    long ftell(FILE *stream);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    int getc(FILE *stream);
    struct tm *gmtime(const time_t *time);
    double ldexp(double x, int exp);
    struct tm *localtime(const time_t *time);
    double log(double x);
    double log10(double x);
    double log2(double x);
    time_t mktime(struct tm *tm);
    double pow(double x, double y);
    int remove(const char *path);
    int rename(const char *oldPath, const char *newPath);
    char *setlocale(int category, const char *locale);
    int setvbuf(FILE *stream, char *buf, int mode, size_t size);
    void (*signal(int sig, void (*func)(int)))(int);
    double sin(double x);
    double sinh(double x);
    int snprintf(char *str, size_t size, const char *format, ...);
    int sprintf(char *str, const char *format, ...);
    int printf(const char *format, ...);
    void srand(unsigned int seed);
    int strcoll(const char *s1, const char *s2);
    char *strerror(int errnum);
    size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
    char *strpbrk(const char *s, const char *accept);
    double strtod(const char *nptr, char **endptr);
    int system(const char *command);
    double tan(double x);
    double tanh(double x);
    time_t time(time_t *tloc);
    FILE *tmpfile();
    char *tmpnam(char *s);
    void *memset(void *s, int c, size_t n);
    void *memcpy(void *dest, const void *src, size_t n);
    size_t strlen(const char *s);
    void *malloc(size_t size);
    void *calloc(size_t num, size_t size);
    void *memmove(void *dest, const void *src, size_t n);
    void free(void *ptr);
    void *realloc(void *ptr, size_t size);
    double fabs(double x);
    int abs(int n);
    int ifloor(double x);
    int iceil(double x);
    double sqrt(double x);
    char *getenv(const char *name);
    int strcmp(const char *s1, const char *s2);
    int strcasecmp(const char *s1, const char *s2);
    int strncmp(const char *s1, const char *s2, size_t n);
    int strncasecmp(const char *s1, const char *s2, size_t n);
    int toupper(int c);
    int tolower(int c);
    char *strncpy(char *dest, const char *src, size_t n);
    long int strtol(const char *nptr, char **endptr, int base);
    unsigned long int strtoul(const char *nptr, char **endptr, int base);
    char *strcat(char *dest, const char *src);
    char *strsep(char **stringp, const char *delim);
    char *strstr(const char *haystack, const char *needle);
    char *strrchr(const char *s, int c);
    void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
    char *strcpy(char *dest, const char *src);
    char *stpcpy(char *dest, const char *src);
    char *strchr(const char *s, int c);
    size_t strnlen(const char *s, size_t maxlen);
    size_t strspn(const char *s, const char *accept);
    size_t strcspn(const char *s, const char *reject);
    int memcmp(const void *s1, const void *s2, size_t n);
    void *memchr(const void *s, int c, size_t n);
    int isspace(int c);
    int isalpha(int c);
    int isdigit(int c);
    struct lconv *localeconv();
    int rand();
    int ungetc(int c, FILE *stream);
    
    void int32_to_str(char* str, int32_t num) {
    uint8_t is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    uint8_t len = 0;
    do {
        str[len++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    if (is_negative) {
        str[len++] = '-';
    }
    str[len] = '\0';
    // Reverse the string
    for (uint8_t i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

