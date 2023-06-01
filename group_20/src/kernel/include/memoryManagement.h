#ifndef MEMORY
#define MEMORY

#include <stdint.h> /* Include standard integer types */
#include <stddef.h> /* Include standard definitions */


typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;


void init_kernel_memory(uint32_t* kernel_end);

// BASIC PAGING FUNCTIONS
extern void init_paging(); /* Initializes paging */
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); /* Maps a virtual address to a physical address */

//
extern char* pmalloc(size_t size); /* Allocates memory of given size with page alignment */
extern void* malloc(size_t size); /* Allocates memory of given size */
extern void free(void *mem); /* Frees memory previously allocated */

//
extern void* memcpy(void* dest, const void* src, size_t num ); /* Copies num bytes from src to dest */
extern void* memset (void * ptr, int value, size_t num ); /* Sets num bytes starting from ptr to value */
extern void* memset16 (void *ptr, uint16_t value, size_t num); /* Sets num bytes starting from ptr to a 16-bit value */

#endif