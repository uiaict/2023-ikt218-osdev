#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

char* hex32_to_str(char buffer[], unsigned int val)
{
	char const lut[] = "0123456789ABCDEF";
	for (int i = 0; i < 4; i++)
	{
		buffer[i*2+0] = lut[(val >> (28-i*8)) & 0xF];
		buffer[i*2+1] = lut[(val >> (24-i*8)) & 0xF];
	}
	buffer[8] = 0;
	return buffer;
}

char* int32_to_str(char buffer[], int val)
{
	char* b = buffer;
	// negation
	if (val < 0) { *b++ = '-'; val *= -1; }
	// move to end of repr.
	int tmp = val;
	do { ++b; tmp /= 10;  } while (tmp);
	*b = 0;
	// move back and insert as we go
	do {
		*--b = '0' + (val % 10);
		val /= 10;
	} while (val);
	return buffer;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
