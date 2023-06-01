/*
* Code retrieved from https://github.com/perara/ikt218-advanced-operating-systems/blob/1ce6e0b734968ad952275b8bbff049b8b690c5fb/src/stdlib/stdlib/cpp/exception.h#L11
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdint.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__);

void panic(const char *message, const char *file, uint32_t line);

#endif 