#include "system.h"

void* memset (void *dest, int val,  size_t len) // this function sets memory addresses to be a spesific value often zero
{
  register unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0) // for every memmory adress set to be val or input value. 
    *ptr++ = val;
  
};