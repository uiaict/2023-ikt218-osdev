#include <stdint.h>

void unset_screen();
void clear_screen();
void print(const char* str, ...);
void scroll_up();
void scroll_down();
void toggle_cursor();
void backspace();
void terminal_putchar(char c);