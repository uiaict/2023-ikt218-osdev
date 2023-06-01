#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

extern u16int *video_memory;
// Write a single character out to the screen.
extern void monitor_put(char c);

// Clear the screen to all black.
extern void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
extern void monitor_write(char *c);

extern void monitor_write_hex(u32int n);

extern void monitor_write_dec(u32int n);
#endif // MONITOR_H