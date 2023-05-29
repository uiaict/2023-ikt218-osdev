#include "system.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "time.h"
#include "/home/tuvaea/ikt218-osdev/group_tuva/src/kernel/include/common.h"


void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

// The VGA framebuffer starts at 0xB8000.
u16int *video_memory = (u16int *)0xB8000;
// Stores the cursor position.
u8int cursor_x = 0;
u8int cursor_y = 0;



// Updates the hardware cursor.
static void move_cursor()
{
    // The screen is 80 characters wide...
    u16int cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursorLocation);      // Send the low cursor byte.
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


int printf(const char *string, ...)
    {
        volatile char *video = (volatile char*)0xB8000;
        while( *string != 0 )
        {
            *video++ = *string++;
            *video++ = 0x0F;
        }
    }





