#ifndef MONITOR_H
#define MONITOR_H
/* Monitor setup */

// Video memory address
u16int *video_memory;

// Writes a byte to the command port
void monitor_put(u8int c, u8int bg_color, u8int fg_color);


#endif