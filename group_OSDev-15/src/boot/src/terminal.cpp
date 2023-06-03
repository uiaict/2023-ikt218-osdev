/* Hardware text mode color constants. */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <terminal.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
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
 

 
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY);
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
	if(c != '\n'){

	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);

	}
}
 //https://stackoverflow.com/questions/62681397/how-to-implement-newlin-n-to-my-kernel
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if(c == '\n')
        {
			if(++terminal_row ==VGA_HEIGHT){
					terminal_row = 0;
					terminal_column= 0;
					terminal_initialize(); 
			}
			else {
            terminal_column = 0;
			}
        }
	else if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT){
			terminal_row = 0;
			terminal_initialize(); 
		}
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

void monitor_write_dec(uint32_t n){

	if (n==0x0)
		terminal_writestring("0x0");
	 if (n==0x1)
		terminal_writestring("0x1");
	else if (n==0x2)
		terminal_writestring("0x2");
	else if (n==0x3)
		terminal_writestring("0x3");
	else if (n==0x4)
		terminal_writestring("0x4");
	else if (n==0x5)
		terminal_writestring("0x5");
	else if (n==0x6)
		terminal_writestring("0x6");
	else if (n==32)
		terminal_writestring("0x32");
	else if (n==0x32)
		terminal_writestring("0x32");
}


void terminal_write_dec(uint32_t n)
{

    if (n == 0)
    {
        terminal_putchar('0');
        return;
    }

    int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    terminal_writestring(c2);

}


 uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}
