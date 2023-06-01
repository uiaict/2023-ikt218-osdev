#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h> /* Include standard integer types */
#include <stddef.h> /* Include standard definitions */

/*
 * Definition of a struct that represents a memory allocation.
 * It contains a status field (0 or 1) indicating if the memory
 * is currently allocated or not, and a size field indicating
 * the size of the allocated memory in bytes.
 */
typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

/*Function declarations*/

//Functions in memory_management.c:
void init_kernel_memory(uint32_t* kernel_end);
void print_memory_layout();
void free(void *mem); /* Frees memory previously allocated */
void pfree(void *mem);
char* pmalloc(); /* Allocates memory of given size with page alignment */
void* malloc(size_t size); /* Allocates memory of given size */
void *my_memset(void *str, int c, int len);

//Functions in paging.c:
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); /* Maps a virtual address to a physical address */
void paging_enable();
void init_paging(); /* Initializes paging */


#endif