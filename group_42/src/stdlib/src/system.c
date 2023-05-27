#include "system.h"

void* memset (void *dest, int val,  size_t len)
{
  register unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0)
    *ptr++ = val;
  
};