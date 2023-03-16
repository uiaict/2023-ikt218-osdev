#ifndef MONITOR_H
#define MONITOR_H
/* Monitor setup */

// Video memory address
extern u16int *video_memory;

// Writes a byte to the command port
extern void monitor_put(u8int c, u8int bg_color, u8int fg_color);


#endif