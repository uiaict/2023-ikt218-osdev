#ifndef MONITOR_H
#define MONITOR_H
/* Monitor setup */
#include "common.h"

// Video memory address
extern u16int *video_memory;

// Writes a byte to the command port
extern void monitor_put(u8int c, u8int bg_color, u8int fg_color);

// Write a null-terminated string to the terminal
extern void monitor_write(char *c, u8int bg_color, u8int fg_color);

// Shows the cursor on the screen
extern void show_cursor();

// Clears the screen
extern void clear_monitor();

#endif