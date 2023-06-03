#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdint.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

    void terminal_init();
    void terminal_write(const char* str);
    void terminal_write_char(char c);

#ifdef __cplusplus
}
#endif
#endif