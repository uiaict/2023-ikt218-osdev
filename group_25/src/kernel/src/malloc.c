#include "memory.h"
#include <system.h>

#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;

// Initialize kernel memory manager
void init_kernel_memory(uint32_t* kernel_end){
    last_alloc = kernel_end + 0x1000;
    heap_begin = last_alloc;
    pheap_end = 0x400000;
    pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
    heap_end = pheap_begin;
    memset((char *)heap_begin, 0, heap_end - heap_begin);
    pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);
}

// Print memory layout
void print_memory_layout(){
    printf("Memory used: %d bytes\n", memory_used);
    printf("Memory free: %d bytes\n", heap_end - heap_begin - memory_used);
    printf("Heap size: %d bytes\n", heap_end - heap_begin);
    printf("Heap start: 0x%x\n", heap_begin);
    printf("Heap end: 0x%x\n", heap_end);
    printf("PHeap start: 0x%x\n", pheap_begin);
    printf("PHeap end: 0x%x\n", pheap_end);
}

// Free memory block
void free(void *mem){
    alloc_t *alloc = (mem - sizeof(alloc_t));
    memory_used -= alloc->size + sizeof(alloc_t);
    alloc->status = 0;
}

// Free page-aligned memory block
void pfree(void *mem){
    if(mem < pheap_begin || mem > pheap_end){
        return;
    }
    uint32_t ad = (uint32_t)mem;
    ad -= pheap_begin;
    ad /= 4096;
    pheap_desc[ad] = 0;
}

// Allocate page-aligned memory block
char* pmalloc(size_t size){
    // Loop through memory blocks to find empty block
    for(int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++){
        if(pheap_desc[i]){
            continue;
        }
        pheap_desc[i] = 1;
        return (char *)(pheap_begin + i*4096);
    }
    printf("pmalloc: Could not find empty memory block\n");
    return 0;
}

// Allocate a block of memory
void* malloc(size_t size){
    if(!size) return 0;

    // Loop through all blocks to find an available block with enough size
    uint8_t *mem = (uint8_t *)heap_begin;
    while((uint32_t)mem < last_alloc)
    {
        alloc_t *a = (alloc_t *)mem;
        if(!a->size)
            goto nalloc;
        if(a->status) {
            mem += a->size;
            mem += sizeof(alloc_t);
            mem += 4;
            continue;
        }
        // If the block is not allocated and its size is big enough,
        // adjust its size, set the status, and return the location.
        if(a->size >= size)
        {
            a->status = 1;
            memset(mem + sizeof(alloc_t), 0, size);
            memory_used += size + sizeof(alloc_t);
            return (char *)(mem + sizeof(alloc_t));
        }
        mem += a->size;
        mem += sizeof(alloc_t);
        mem += 4;
    }

    nalloc:;
    if(last_alloc + size + sizeof(alloc_t) >= heap_end)
    {
        printf("Cannot allocate bytes! Out of memory.\n");
    }
    alloc_t *alloc = (alloc_t *)last_alloc;
    alloc->status = 1;
    alloc->size = size;

    last_alloc += size;
    last_alloc += sizeof(alloc_t);
    last_alloc += 4;
    memory_used += size + 4 + sizeof(alloc_t);
    memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
    return (char *)((uint32_t)alloc + sizeof(alloc_t));
}

// Copy memory from src to dest
void* memcpy(void* dest, const void* src, size_t count ){
    char* src8 = (char*)src;
    char* dst8 = (char*)dest;
    if (count & 1) {
        dst8[0] = src8[0];
        dst8 += 1;
        src8 += 1;
    }
    count /= 2;
    while (count--) {
        dst8[0] = src8[0];
        dst8[1] = src8[1];

        dst8 += 2;
        src8 += 2;
    }
    return (void*)dest;
}

// Function to set a block of memory with a 16-bit value
void* memset16 (void *ptr, uint16_t value, size_t num){
    uint16_t* p = ptr;
    while(num--)
        *p++ = value;
    return ptr;
}

// Function to set a block of memory with a byte value
void* memset (void * ptr, int value, size_t num ){
    unsigned char* p=ptr;
    while(num--)
        *p++ = (unsigned char)value;
    return ptr;
}