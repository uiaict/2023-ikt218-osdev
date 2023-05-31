/*

        https://blog.igorw.org/2015/03/04/scancode-to-ascii/
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "interrupt_service_routines.h"

void keyboard_handler(registers_t *regs, void * /* context */);


#endif