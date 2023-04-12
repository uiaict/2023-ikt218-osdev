#include "stdint.h"
#include <stddef.h>

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

// Initialize kernel memory + memory allocation
void init_kernel_memory(uint32_t* kernel_end);
void print_memory_layout();

void *malloc(size_t size);
void free(void *ptr);

// Helper functions
void* memcpy(void* dest, const void* src, size_t count );
void* memset16 (void *ptr, uint16_t value, size_t num);
void* memset (void * ptr, int value, size_t num );

// Paging
void init_paging();
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);
