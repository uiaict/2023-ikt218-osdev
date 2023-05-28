#include "screen.h"


int cursor_position = 0;

void set_cursor(int new_offset)
{
    cursor_position = new_offset;
};

/* Print a char on the screen at col , row , or at cursor position */
void print_char(char character, int col, int row, char attribute_byte)
{
    /* Create a byte ( char ) pointer to the start of video memory */
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

    /* If attribute byte is zero , assume the default style . */
    if (!attribute_byte)
    {
        attribute_byte = WAKE_UP_NEO;
    }

    /* Get the video memory offset for the screen location */
    int offset;
    /* If col and row are non - negative , use them for offset . */
    if (col >= 0 && row >= 0)
    {
        offset = get_screen_offset(col, row);
        /* Otherwise , use the current cursor position . */
    }
    else
    {
        offset = cursor_position;
    }

    // If we see a newline character , set offset to the end of
    // current row , so it will be advanced to the first col
    // of the next row .
    if (character == '\n')
    {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(79, rows);
        // Otherwise , write the character and its attribute byte to
        // video memory at our calculated offset .
    }
    else
    {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }

    // Update the offset to the next character cell , which is
    // two bytes ahead of the current cell .
    offset += 2;
    /*
    TO DO NEXT TIME
        // Make scrolling adjustment , for when we reach the bottom
        // of the screen .
        offset = handle_scrolling(offset);*/

    // Update the cursor position on the screen device .
    set_cursor(offset);
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
    /*if I want to set a character at
    row 3, column 4 of the display, then the character cell of that will be at a (decimal)
    offset of 488 ((3 * 80 (i.e. the the row width) + 4) * 2 = 488) from the start
    of video memory*/
    int offset = ((row * MAX_COLS) + col) * 2;
    return offset;
}

void print_at(char *message, int col, int row)
{
    int i = 0;
    while (message[i] != 0)
    {
        // Print a char, and update the cursor after.
        print_char(message[i++], col, row, WAKE_UP_NEO);
        col++;

        // If we reached the end of a row, we have to move down.
        if (col >= MAX_COLS)
        {
            col = 0;
            row++;
        }
    }
}

void clear_screen()
{
    int row = 0;
    int col = 0;

    /* Loop through video memory and write blank characters . */
    for (row = 0; row < MAX_ROWS; row++)
    {
        for (col = 0; col < MAX_COLS; col++)
        {
            print_char(' ', col, row, WAKE_UP_NEO);
        }
    }
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

void print(char *text)
{
    int counter = 0;
    while (text[counter] != 0)
    {
        // Print a char, and update the cursor after.
        print_char(text[counter++], -1, -1, WAKE_UP_NEO);
    }
}

void play_intro()
{
    // Siden vi ikke vil ha standard plassering på disse,
    // så gjør vi denne manuelt
    print_at("--Welcome to asakOS!--", 29, 8);
    print_at("Hello World!", 34, 9);

    // Til slutt må vi sette cursor til under beskjeden
    set_cursor(get_screen_offset(0, 13));
}

/* Advance the text cursor , scrolling the video buffer if necessary . */
/*int handle_scrolling(int cursor_offset)
{
    // If the cursor is within the screen , return it unmodified .
    if (cursor_offset < MAX_ROWS*MAX_COLS*2)
    {
        return cursor_offset;
    }

    //Shuffle the rows back one .
    int i ;
    for (i=1; i<MAX_ROWS; i++)
    {
        memory_copy( get_screen_offset(0, i) + VIDEO_ADDRESS,
                    get_screen_offset(0, i-1) + VIDEO_ADDRESS,
                    MAX_COLS*2
                    );
    }

    // Blank the last line by setting all bytes to 0
    char* last_line = get_screen_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
    for (i=0; i<MAX_COLS*2; i++)
    {
        last_line[i] = 0;
    }

    // Move the offset back one row , such that it is now on the last
    // row , rather than off the edge of the screen .
    cursor_offset -= 2*MAX_COLS;

    // Return the updated cursor position .
    return cursor_offset;
}
*/
