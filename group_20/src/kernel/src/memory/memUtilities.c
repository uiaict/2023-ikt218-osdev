#include "memoryManagement.h"   // Include the header file that defines the functions
#include "screen.h"

#include <stdint.h>          // Include the standard integer types
#include <stddef.h>          // Include the standard size types

// Function to set a block of memory with a byte value
void* memset (void * ptr, int value, size_t num )
{
    unsigned char* p=ptr;     // Cast the pointer to unsigned char*
    while(num--)
        *p++ = (unsigned char)value;   // Set each byte to the given value
    return ptr;               // Return the pointer to the block of memory
}