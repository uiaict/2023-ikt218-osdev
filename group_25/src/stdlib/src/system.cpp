#include "system.h"

// Find the length of a c-string
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}