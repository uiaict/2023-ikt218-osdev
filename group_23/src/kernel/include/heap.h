#ifndef HEAP_H
# define HEAP_H
#include "common.h"
#include <stdint.h>
#include <stddef.h>

#define MAX_PAGE_ALIGNED_ALLOCS 32

extern uint32_t last_alloc;
extern uint32_t heap_end;
extern uint32_t heap_begin;
extern uint32_t pheap_begin;
extern uint32_t pheap_end;
extern uint8_t *pheap_desc;
extern uint32_t memory_used;

typedef struct alloc_t {
    uint8_t status;
    uint32_t size;
} alloc_t;


void init_kernel_memory(uint32_t* kernel_end);
void print_memory_layout();
void free(void *mem);
void pfree(void *mem);
char* pmalloc(size_t size);
void* malloc(size_t size);



#endif // HEAP_H