#include <stdint.h>

#define SC_MAX 83

struct lookup_map
{
    // lookup_map is strictly for making the hardcoded lookup table easeier to read and edit.
    // Scancodes are used to index into an array of lookup_map instances.
    const char* scancode;
    const char* character;
};

const char* scancode_to_ascii(uint8_t scancode);