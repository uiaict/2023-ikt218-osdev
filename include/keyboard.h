#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <system.h>
#include <isr.h>

void init_keyboard();


void keyboard_handler(registers_t regs);
#endif