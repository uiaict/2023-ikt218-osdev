#include "common.h"
#include "monitor.h"

// Monitor setup
// Set up VGA width and height
static const int MONITOR_WIDTH = 80;
static const int MONITOR_HEIGHT = 25;

// Size of the video memory
static const int MONITOR_SIZE = 2 * MONITOR_WIDTH * MONITOR_HEIGHT;     // (2 bytes per char, 80 columns and 25 rows)

// VGA ports
static const u16int MONITOR_COMMAND_PORT = 0x3D4;
static const u16int MONITOR_DATA_PORT = 0x3D5;

// VGA commands
static const u8int MONITOR_HIGH_BYTE_COMMAND = 14;  // Sets high byte of cursor position (= row)
static const u8int MONITOR_LOW_BYTE_COMMAND = 15;   // Sets low byte of cursor position (= column)

// Cursor position variables
static u8int cursor_column = 0;
static u8int cursor_row = 0;

// Video memory address
u16int *video_memory = (u16int *)0xB8000;

// Move the hardware cursor
static void move_cursor() {
    u16int location = cursor_row * MONITOR_WIDTH + cursor_column;
    outb(MONITOR_COMMAND_PORT, MONITOR_HIGH_BYTE_COMMAND);  // Tells VGA board we are setting the cursor row
    outb(MONITOR_DATA_PORT, location >> 8);          // Sets the row
    outb(MONITOR_COMMAND_PORT, MONITOR_LOW_BYTE_COMMAND);   // Tells VGA board we are setting the cursor column
    outb(MONITOR_DATA_PORT, location);               // Send the column
}

// Scroll text on screen up one line
static void scroll_monitor() {
    // Space character with color attribute
    u8int attribute_byte = (0 << 4) | (15 & 0x0F);          // Black background, white foreground
    u16int blank = 0x20 | (attribute_byte << 8);            // 0x20 is the space character

    // Scroll up if the cursor has reached the bottom of the screen
    if (cursor_row >= MONITOR_HEIGHT) {
        int i;
        // Moves the whole text on the screen one line up in the video memory
        for (i = 0 * MONITOR_WIDTH; i < (MONITOR_HEIGHT - 1) * MONITOR_WIDTH; i++) {
            video_memory[i] = video_memory[i + MONITOR_WIDTH];
        }

        // Then write blank characters to the last line
        for (i = (MONITOR_HEIGHT - 1) * MONITOR_WIDTH; i < MONITOR_HEIGHT * MONITOR_WIDTH; i++) {
            video_memory[i] = blank;
        }
        
        // Finally set the cursor to the last line
        cursor_row = MONITOR_HEIGHT - 1;
    }
}

// Function to show the cursor
void show_cursor() {
    outb(MONITOR_COMMAND_PORT, 0x0A);
    outb(MONITOR_DATA_PORT, (inb(MONITOR_DATA_PORT) & 0xC0) | 14);  // cursor start = line 14 in the character cell

    outb(MONITOR_COMMAND_PORT, 0x0B);
    outb(MONITOR_DATA_PORT, (inb(MONITOR_DATA_PORT) & 0xE0) | 15);  // cursor end = line 15 in the character cell
}


// Writes a byte to the command port
void monitor_put(u8int c, u8int bg_color, u8int fg_color) {
    // Get the color byte (high nibble is background color and low nibble is foreground color)
    u8int color = (bg_color << 4) | (fg_color & 0x0F);

    // Get the attribute byte, which is the top 8 bits of the word we write to the video memory
    u16int attribute = color << 8;

    u16int *location; // Pointer to the video memory location

    // Backspace moves cursor to the previous column
    if (c == '\b') {
        if (cursor_column > 0) {
            cursor_column--;
        }
        // Go to previous row if we are at the first column
        else if (cursor_row > 0) {
            cursor_column = MONITOR_WIDTH - 1;
            cursor_row--;
        }
    }
    // Newline moves cursor to the first column of the next row
    else if (c == '\n') {
        cursor_column = 0;
        cursor_row++;
    }
    // Carriage return moves cursor to the first column
    else if (c == '\r') {
        cursor_column = 0;
    }
    // Tab moves cursor to next tab stop (increasing column until it is a multiple of 8)
    else if (c == '\t') {
        if (cursor_column < MONITOR_WIDTH - 8) {
            cursor_column = (cursor_column + 8) & ~(8 - 1);
        }
        else {  // Set to last column if there is no more room
            cursor_column = MONITOR_WIDTH - 1;
        }
    }
    // Any other character is written to the video memory
    else if (c >= ' ') {
        location = video_memory + (cursor_row * MONITOR_WIDTH + cursor_column);
        *location = c | attribute;      // This sets the character as the lower byte of "attribute"
        cursor_column++;
    }

    // Safety check in case we have reached the end
    if (cursor_column >= MONITOR_WIDTH) {
        cursor_column = 0;
        cursor_row++;
    }

    // Scroll
    scroll_monitor();

    // Move the hardware cursor
    move_cursor();
}

// Writes a null-terminated string to the terminal
void monitor_write(char *c, u8int bg_color, u8int fg_color) {
    while (*c) {
        monitor_put(*c++, bg_color, fg_color);
    }
}

// Clears the monitor by writing black blanks to the whole screen
void clear_monitor() {
    // Space character with color attribute
    u8int attribute_byte = (0 << 4) | (15 & 0x0F);           // Black background, white foreground
    u16int blank = 0x20 | (attribute_byte << 8);             // 0x20 is the space character

    int i;
    for (i = 0; i < MONITOR_WIDTH * MONITOR_HEIGHT; i++)     // Loop thorough the whole video memory on screen
    {
        video_memory[i] = blank;
    }

    show_cursor();  // Show the cursor
    // Move the hardware cursor back to the start.
    cursor_row = 0;
    cursor_column = 0;
    move_cursor();
}