#include "monitor.h"
#include "common.h"
#include <stddef.h>

static u8int cursor_x = 0;
static u8int cursor_y = 0;

u16int *video_memory = (u16int *)0xB8000;

void memsetv2(void* ptr, int value, size_t num)
{
    unsigned char* bytes = (unsigned char*)ptr;
    for (size_t i = 0; i < num; i++)
    {
        bytes[i] = (unsigned char)value;
    }
}

void* memcpy(void* destination, const void* source, size_t num)
{
    unsigned char* dest = (unsigned char*)destination;
    const unsigned char* src = (const unsigned char*)source;
    for (size_t i = 0; i < num; i++)
    {
        dest[i] = src[i];
    }
    return destination;
}

static void move_cursor()
{
   // The screen is 80 characters wide...
   u16int cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
} 



void monitor_put(char c)
{
    // The background colour is black (0), the foreground is white (15).
    u8int backColour = 0;
    u8int foreColour = 15;

    // The attribute byte is made up of two nibbles - the lower being the
    // foreground colour, and the upper the background colour.
    u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    u16int attribute = attributeByte << 8;
    u16int *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;

        attributeByte = (backColour << 4) | (foreColour & 0x0F);
        attribute = attributeByte << 8;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
   }

    if (cursor_y >= 25)
    {
        int i;
        // Move each line up by one row
        for (i = 0; i < 24; i++)
        {
            memcpy(video_memory + i * 80, video_memory + (i + 1) * 80, 80 * sizeof(u16int));
        }
        // Clear the last line
        u16int attribute = (0 << 4) | (15 & 0x0F); // black background, white foreground
        u16int blank = 0x20 | (attribute << 8);    // space character with the attribute
        memsetv2(video_memory + 24 * 80, blank, 80 * sizeof(u16int));
        for (i = 0; i < 80; i++)
        {
            video_memory[24 * 80 + i] = blank;
        }
        cursor_y = 24;
    }

   // Scroll the screen if needed.
   // Move the hardware cursor.
   move_cursor();
} 


 void monitor_clear()
{
   // Make an attribute byte for the default colours
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
} 

void monitor_write(char *c)
{
   int i = 0;
   while (c[i])
   {
       monitor_put(c[i++]);
   }
}

void monitor_write_hex(u32int n)
{
    if (n == 0)
    {
        monitor_put('0');
        return;
    }

    char buffer[32];
    int i = 0;

    while (n > 0)
    {
        u32int digit = n % 16;
        if (digit < 10)
            buffer[i++] = '0' + digit;
        else
            buffer[i++] = 'A' + (digit - 10);
        n /= 16;
    }

    while (i > 0)
    {
        monitor_put(buffer[--i]);
    }
}


void monitor_write_dec(u32int n)
{
    if (n == 0)
    {
        monitor_put('0');
        return;
    }

    char buffer[32];
    int i = 0;

    while (n > 0)
    {
        buffer[i++] = '0' + (n % 10);
        n /= 10;
    }

    while (i > 0)
    {
        monitor_put(buffer[--i]);
    }
} 