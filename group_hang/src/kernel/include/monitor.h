#ifndef MONITOR_H
#define MONITOR_H
#include <stddef.h>

#include "common.h"

extern u16int *video_memory;

extern void memsetv2(void* ptr, int value, size_t num);

void* memcpy(void* destination, const void* source, size_t num);

// Write a single character out to the screen.
extern void monitor_put(char c);

// Clear the screen to all black.
extern void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
extern void monitor_write(char *c);

extern void monitor_write_hex(u32int n);

extern void monitor_write_dec(u32int n);


#endif // MONITOR_H