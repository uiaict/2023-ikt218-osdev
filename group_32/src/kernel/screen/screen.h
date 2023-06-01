#ifndef SCREEN
#define SCREEN

#include <stdint.h>
#include <stddef.h>

void screenInitialize();
void ScreenSetcolor(uint8_t color);
void screenWrite(const char* data);

#endif