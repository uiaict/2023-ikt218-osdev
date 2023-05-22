#include "/workspaces/ikt218/group-24/src/stdlib/include/system.h"

size_t strlen(const char* str) 
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}