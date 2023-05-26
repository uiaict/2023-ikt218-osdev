#include "system.h"

size_t strlen(const char* str) 
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}

void *memset(void* ptr, int value, size_t num) {
   unsigned char* ptr_byte = (unsigned char*)ptr;

   for (size_t i = 0; i < num; ptr_byte[i] = (unsigned char)value, i++);   
   return ptr;
};