#ifndef MEMORY
#define MEMORY

#include <stdint.h> /* Include standard integer types */
#include <stddef.h> /* Include standard definitions */

typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;


/* Function declarations for paging operations */
void start_paging(); /* Initializes paging */
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); /* Maps a virtual address to a physical address */

#endif