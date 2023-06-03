// Modified code from JamesM's tutorial.

#include "print.h"
#include "common.h"

#define WIDTH 80
#define HEIGHT 25
#define TEXT_COLOR 2
#define BACKGROUND_COLOR 0

// The VGA framebuffer starts at 0xB8000.
u16int *video_memory = (u16int *)0xB8000;

// Stores the cursor position.
// Initialize cursor position to 0,0 (top left)
u8int cursor_x = 0;
u8int cursor_y = 0;


// Move cursor
static void move_cursor()
{
   u16int cursorLocation = cursor_y * WIDTH + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
} 

// Scrolls the text on the screen up by 3 lines.
static void scroll()
{
    u8int color = (BACKGROUND_COLOR << 4) | (TEXT_COLOR & 0x0F);
    u16int blank = 0x20 | (color << 8);

   // Scroll up 3 lines when hitting the buttom line on the screen.
   if(cursor_y >= HEIGHT)
   {
       // Move the text on the screen 3 line upwards.
       int i;
       for (i = 0*WIDTH; i < (HEIGHT-1)*WIDTH*3; i++)
       {
           video_memory[i] = video_memory[i+WIDTH*3];
       }

       // Blank the 3 last lines on the screen.
       for (i = (HEIGHT-3)*WIDTH; i < HEIGHT*WIDTH; i++)
       {
           video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = HEIGHT-3;
   }
} 


// Writes one char.
void print_char(char c)
{
   // Set both background and text colour.
   u8int backColor = BACKGROUND_COLOR;
   u8int textColor = TEXT_COLOR;

   // Set the color of the backgorund and the text.
   u8int  attributeByte = (backColor << 4) | (textColor & 0x0F);
   // Add the color to the byte that is going to be written to the video memory.
   u16int attribute = attributeByte << 8;
   u16int *location;

   // Handle a backspace, by moving the cursor back one space
   // and delete the character.
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
       location = video_memory + (cursor_y*WIDTH + cursor_x);
       *location = ' ' | attribute;
   }

   // Move the cursor 5 steps forward if tab is pressed.
   // or to nearest 5th position.
   else if (c == '\t')
   {
       cursor_x = (cursor_x+5) & ~(5-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Newline
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
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
   if (cursor_x >= WIDTH)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.
   scroll();
   // Move the hardware cursor.
   move_cursor();
} 


// Clears the screen.
void clear_screen()
{
   // Make an attribute byte for the default colours
   u8int attributeByte = (BACKGROUND_COLOR << 4) | (TEXT_COLOR & 0x0F);
   u16int blank = ' ' | (attributeByte << 8);

   int i;
   for (i = 0; i < WIDTH*HEIGHT; i++)
   {
       video_memory[i] = blank;
   }

   // Set courser position to 0,0 (top left)
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
} 


// Print string.
void print_string(char *c)
{
   int i = 0;
   while (c[i])
   {
       print_char(c[i++]);
   }
} 

void print_hex(u32int n)
{
    s32int tmp;

    print_string("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            print_char (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            print_char( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        print_char (tmp-0xA+'a');
    }
    else
    {
        print_char (tmp+'0');
    }

}

void print_dec(u32int n)
{

    if (n == 0)
    {
        print_char('0');
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    print_string(c2);

}