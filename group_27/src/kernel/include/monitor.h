// monitor.h -- Defines the interface for monitor.h
//              From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"
#include <stdint.h>
#include <stddef.h>

void monitor_initialize(void) ;
void monitor_setcolor(uint8_t color);
//void monitor_putentryat(char c, uint8_t color, size_t x, size_t y);

void monitor_put(char c, bool increase_buffer);
void monitor_clear();
void monitor_write(const char* data, size_t size);
void monitor_write_hex(uint32_t n);
void monitor_write_dec(uint32_t n);
void set_prefix(char* c);
void print_logo();

#endif // MONITOR_H