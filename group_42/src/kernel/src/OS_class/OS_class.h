#include <stdint.h>
#include <stdlib.h>

#include"../keyboard/keyboard.h"
#include"../memory/functions.h"
#include"../PIT/pit.h"

#define OS_class_H

class IJI_OS{
    public:
    int tick = 0;
    int tmp = 0;
    int color = 0x0B;
    volatile char *address = (volatile char*)0xB8000;
    volatile char *next_address = (volatile char*)0xB8000 + 160;
    int line = 0;

    void next_line();
    void write_string(const char *string);
    void write_char(char c);
    void write_integer(char* string, uint32_t a);
    void write_hexadecimal(char* string, uint32_t a);
    void print_memory_layout();
    void interrupt_handler_3(UiAOS::CPU::ISR::registers_t regs);
    void interrupt_handler_2(UiAOS::CPU::ISR::registers_t regs);
    void interrupt_handler_1(UiAOS::CPU::ISR::registers_t regs);
    void init();
    void clearScreen();
};