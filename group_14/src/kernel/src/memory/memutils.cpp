#include "../include/memory.h"   // Include the header file that defines the functions

#include <stdint.h>          // Include the standard integer types
#include <stddef.h>          // Include the standard size types

// Function to copy memory from source to destination
void* custom_memcpy(void* dest, const void* src, size_t count )
{
    char* dst8 = (char*)dest;  // Cast the destination pointer to char*
    char* src8 = (char*)src;   // Cast the source pointer to char*

    if (count & 1) {           // If the count is odd
        dst8[0] = src8[0];     // Copy one byte from source to destination
        dst8 += 1;             // Increment destination pointer by one byte
        src8 += 1;             // Increment source pointer by one byte
    }

    count /= 2;                // Divide the count by two to copy 2 bytes at a time
    while (count--) {          // Loop through each pair of 2 bytes
        dst8[0] = src8[0];     // Copy the first byte of the pair from source to destination
        dst8[1] = src8[1];     // Copy the second byte of the pair from source to destination

        dst8 += 2;             // Increment destination pointer by 2 bytes
        src8 += 2;             // Increment source pointer by 2 bytes
    }

    return (void*)dest;        // Return the destination pointer
}

// Function to set a block of memory with a 16-bit value
void* custom_memset16 (void *ptr, uint16_t value, size_t num)
{
    uint16_t* p = (uint16_t*)ptr;        // Cast the pointer to uint16_t*
    while(num--)
        *p++ = value;         // Set each 2-byte element to the given value
    return ptr;               // Return the pointer to the block of memory
}

// Function to set a block of memory with a byte value
void* custom_memset (void * ptr, int value, size_t num )
{
    unsigned char* p = (unsigned char*)ptr;     // Cast the pointer to unsigned char*
    while(num--)
        *p++ = (unsigned char)value;   // Set each byte to the given value
    return ptr;               // Return the pointer to the block of memory
}
