

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h> 
#include <stddef.h> 

/*
 struct for memory allocation status = is allocated
 size is the size.
 */
typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;


void init_kernel_memory(uint32_t* kernel_end);



extern void init_paging();
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); 


extern char* pmalloc(size_t size); 
extern void* malloc(size_t size);
extern void free(void *mem); 
extern void* memcpy(void* dest, const void* src, size_t num ); 
extern void* memset (void * ptr, int value, size_t num ); 
extern void* memset16 (void *ptr, uint16_t value, size_t num); 

// functions for getting values for printing memory map in other files
uint32_t get_last_alloc();
uint32_t get_heap_end();
uint32_t get_heap_begin();
uint32_t get_pheap_begin();
uint32_t get_pheap_end();
uint32_t get_memory_used();
#endif