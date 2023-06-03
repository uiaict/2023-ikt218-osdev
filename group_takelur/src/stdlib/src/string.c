/* Contains string manipulation functions */

#include "string.h"

// Get length of string
size_t strlen(const char *s) {
    size__t len = 0;
    // Iterate until null terminator
    while (s[len] != '\0') {
        len++;
    }
    return len;
}