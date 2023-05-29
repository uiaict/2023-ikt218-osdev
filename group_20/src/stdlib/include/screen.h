#ifndef MONITOR_H
#define MONITOR_H

#include <stdint.h>
#include <stddef.h>

static size_t cursorPos = 0; // Keep track of the cursor position

void screenWrite(const char* data);
void screenClear();
void screenWriteCharacter(char character);


#endif