#include "system.h"
#include "vga.h"


#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static size_t vga_row;
static size_t vga_column;
static uint8_t vga_color;
static uint16_t* vga_buffer;

static inline uint16_t vga_entry(unsigned char c)
{
    return (uint16_t)(c | vga_color << 8);
}

static inline void vga_put_char_at(unsigned char c, const size_t x, const size_t y)
{
    vga_buffer[y * VGA_WIDTH + x] = vga_entry(c);
}

static inline void vga_clear_line(const size_t y)
{
    for (size_t x = 0; x < VGA_WIDTH; x++)
        vga_put_char_at(' ', x, y);
}

static void vga_scroll_screen(void)
{
    size_t y;
    for (y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_put_char_at((unsigned char) vga_buffer[y * VGA_WIDTH + x],
                            x, y - 1);
        }
    }
    vga_clear_line(y - 1);
}

static inline void vga_newline(void)
{
    vga_column = 0;
    if (++vga_row == VGA_HEIGHT) {
        vga_scroll_screen();
        vga_row = VGA_HEIGHT - 1;
    }
}

static void vga_clear_screen(void)
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++)
            vga_put_char_at(' ', x, y);
    }
}

void vga_init(void)
{
    vga_set_color(vga_color_light_grey, vga_color_black);
    vga_row = 0;
    vga_column = 0;
    vga_buffer = (uint16_t*)0xB8000;
    vga_clear_screen();
}

inline void vga_set_color(const enum vga_color fg, const enum vga_color bg)
{
    vga_color = (uint8_t)(fg | bg << 4);
}

void vga_putchar(const char c)
{
    if(c == '\n') {
        vga_newline();
        return;
    }
    vga_put_char_at((unsigned char) c, vga_column, vga_row);
    if (++vga_column == VGA_WIDTH) {
        vga_newline();
    }
}

void vga_writestring(const char* data)
{
    for (size_t i = 0; i < strlen(data); i++)
        vga_putchar(data[i]);
}

void vga_backspace(void)
{
    if (vga_column != 0) {
        vga_column -= 1;
        vga_put_char_at(' ', vga_column, vga_row);
    }
}
