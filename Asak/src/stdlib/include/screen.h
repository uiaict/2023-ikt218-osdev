#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

//Attribute byte for our default colour scheme.
//Matrix Colors!
#define WAKE_UP_NEO 0x0A

//Screen device I/O ports.
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

unsigned char port_byte_in ( unsigned short port );
void print_char(char character, int col, int row, char attribute_byte);
int get_cursor();
void set_cursor(int cursor);
int get_screen_offset(int column, int rows);
void clear_screen();
void memory_copy ( char *source, char *dest, int no_bytes);
int handle_scrolling(int cursor_offset);
void print_at (char* message, int col, int row);
void print(char *text);
void print_hex(unsigned int value, unsigned int width, char * buf, int * ptr);
void play_intro();