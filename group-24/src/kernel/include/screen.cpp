#include "screen.h"
#include "common.h"



// Function to unset the screen by shifting the content up
void unset_screen() {
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = vidmem[i+160];
        vidmem[i+1] = vidmem[i+160+1];
    }
}

// Function to clear the screen by setting all characters to space and colors to black on white
void clear_screen() {
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f; // black background, white foreground
    }
}

// Function to print a string on the screen
void print(const char* str, ...) 
{
    // Set cursor position to next line
    char* vidmem = (char*)0xb8000;
    int last_line = 0;
    for (int i = 0; i < 80 * 25 * 2; i += 160) {
        if (vidmem[i] != ' ') {
            last_line = i;
        }
    }

    int i = 0;
    last_line += 160;
    if (last_line >= 80 * 25 * 2) {
        unset_screen(); // If the last line is at the bottom, unset the screen by shifting content
    }
    
    // Print each character of the string
    while (str[i] != '\0') {
        vidmem[last_line + i * 2] = str[i];               // Set character
        vidmem[last_line + i * 2 + 1] = 0x0f;            // Set color attribute to white on blue
        i++;
    }
}

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

static int terminal_column = 0;
static int terminal_row = 0;

uint16_t *terminal_buffer = (uint16_t *)0xB8000;

static void move_cursor()
{
    uint16_t cursor_location = terminal_row * 80 + terminal_column;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursor_location >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursor_location);      // Send the low cursor byte.

    // Turn on the cursor by setting the cursor start and end registers.
    outb(0x3D4, 0x0A); // cursor start register
    outb(0x3D5, 0x00); // set the cursor start to 0
    outb(0x3D4, 0x0B); // cursor end register
    outb(0x3D5, 0x0F); // set the cursor end to 15 (turn on the cursor)
}

//Function that scrolls the terminal up by one line.
void scroll_up()
{
    //Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    //Row 0 is the top, this means we need to scroll up
    if (terminal_row <= 0)
    {
        // Move the current text chunk that makes up the screen
        // forward in the buffer by a line
        int i;
        for (i = 1*80; i <= 25*80; i++)
        {
            terminal_buffer[i - 80] = terminal_buffer[i];
        }

        // The first line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            terminal_buffer[i] = blank;
        }
        // The cursor should now be on the first line.
        terminal_row = 0;
    }
}

//Function that scrolls the terminal up by one line.
void scroll_down()
{
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    if(terminal_row >= 25)
    {
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            terminal_buffer[i] = terminal_buffer[i+80];
        }

        for (i = 24*80; i < 25*80; i++)
        {
            terminal_buffer[i] = blank;
        }
        terminal_row = 24;
    }
}

void backspace()
{   
    //If the terminal_column and terminal_row are both 0, there is nothing to remove, so we just return.
    if(terminal_column == 0 && terminal_row == 0)
    {
        return;
    }
    //If the terminal_column / x coordinate is 0
    else if(terminal_column == 0)
    {
        //Decrement the terminal_row/y coordinate.
        terminal_row--;

        //Find the last non-blank character in the previous line, ignoring newline characters
        int last_non_blank = VGA_WIDTH - 1;
        while (last_non_blank >= 0 && (terminal_buffer[VGA_WIDTH * terminal_row + last_non_blank] & 0xFF) == ' ')
        {
            last_non_blank--;
        }

        // If the last non-blank character is a newline character, place the cursor at the beginning of the line
        if (last_non_blank == -1 || (terminal_buffer[VGA_WIDTH * terminal_row + last_non_blank] & 0xFF) == '\n') 
        {
            terminal_column = 0;
        }
        // Otherwise, set the terminal_column/x coordinate to the last non-blank character in the previous line
        else 
        {
            terminal_column = last_non_blank + 1;
        }
    }
    //Else we are somewhere in a line that's not the start.
    else
    {   
        //Decrement the terminal_column/x coordinate.
        terminal_column--;
    }
    //Fill the current cursor position with a blank character.
    terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] = (terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] & 0xFF00) | ' ';
    //Move the cursor.
    move_cursor();
}

//Defines the function terminal_putchar, that prints a single character to the terminal.
void terminal_putchar(char c)
{
    //Switch statement that takes in the entered character.
    switch(c)
    {
        //If the entered character is a newline the y/vertical cursor is incremented by 1, and the x/horizontal cursor is set to 0
        case '\n':
            terminal_row++;
            terminal_column = 0;
            break;
        //If the character is any other character it gets placed at the current position of the cursors, then the x/horizontal cursor gets incremented.
        default:
            terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] = (terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] & 0xFF00) | c;
            terminal_column++;
            break;
        }

    //If the horizontal cursor reaches the edge of the screen the y/vertical cursor is incremented and the x/horizontal cursor gets set to 0.
    if(terminal_column >= VGA_WIDTH)
    {
        terminal_row++;
        terminal_column = 0;
    }

    //If the cursor reaches the bottom of the screen scroll down.
    if(terminal_row >= VGA_HEIGHT)
    {
        scroll_down();
    }
    //Move the cursor
    move_cursor();
}