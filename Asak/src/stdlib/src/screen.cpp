#include "screen.h"
#include "ports.h"



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

void print_hex(unsigned int value, unsigned int width, char *buf, int *ptr)
{
    int i = width;

    if (i == 0)
        i = 8;

    unsigned int n_width = 1;
    unsigned int j = 0x0F;
    while (value > j && j < UINT32_MAX)
    {
        n_width += 1;
        j *= 0x10;
        j += 0x0F;
    }

    while (i > (int)n_width)
    {
        buf[*ptr] = '0';
        *ptr += 1;
        i--;
    }

    i = (int)n_width;
    while (i-- > 0)
    {
        buf[*ptr] = "0123456789abcdef"[(value >> (i * 4)) & 0xF];
        *ptr += +1;
    }
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

void print(char *message) {
    print_at(message, -1, -1);
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
