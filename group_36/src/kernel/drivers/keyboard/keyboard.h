#include "../../cpu/include/cpu.h"
// #include "stdint.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57

typedef void (*keyboard_callback)(uint8_t scancode, void*);

namespace UiAOS::IO{
    class Keyboard {

    public:
        static void hook_keyboard(keyboard_callback cb, void* ctx);
        static char scancode_to_ascii(uint8_t scancode);
    };
}