//
// Created by per on 1/3/23.
//

#ifndef UIAOS_EXCEPTION_H
#define UIAOS_EXCEPTION_H
#include <stdint.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))


void panic(const char *message, const char *file, uint32_t line);
void panic_assert(const char *file, uint32_t line, const char *desc);




#endif //UIAOS_EXCEPTION_H
