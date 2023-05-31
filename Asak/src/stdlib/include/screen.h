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

void set_cursor(int cursor);
void set_cursor_offset(int offset);

void print(char *text);

// C++ code -> C code
#ifdef __cplusplus
extern "C"
{
#endif
extern int printf(const char* __restrict__ format, ...);
extern void panic(const char* format, ...);
#ifdef __cplusplus
}
#endif

int print_char(char c, int col, int row, char attr);
void print_at (char* message, int col, int row);
void print_hex(unsigned int value, unsigned int width, char * buf, int * ptr);

int get_cursor();
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int get_screen_offset(int col, int row);
int get_cursor_offset();

void clear_screen();
void play_intro();

int handle_scrolling(int cursor_offset);
void memory_copy ( char *source, char *dest, int no_bytes);

