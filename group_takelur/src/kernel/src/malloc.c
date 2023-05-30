#include "kernel/memory.h"
#include <libc/system.h>

#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;

// Initialize the kernel memory manager
void init_kernel_memory(uint32_t* kernel_end)
{
    last_alloc = kernel_end + 0x1000;
    heap_begin = last_alloc;
    pheap_end = 0x400000;
    pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
    heap_end = pheap_begin;
    memset((char *)heap_begin, 0, heap_end - heap_begin);
    pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);
    printf("Kernel heap starts at 0x%x\n", last_alloc);
}

// Print the current memory layout
void print_memory_layout()
{
    printf("Memory used: %d bytes\n", memory_used);
    printf("Memory free: %d bytes\n", heap_end - heap_begin - memory_used);
    printf("Heap size: %d bytes\n", heap_end - heap_begin);
    printf("Heap start: 0x%x\n", heap_begin);
    printf("Heap end: 0x%x\n", heap_end);
    printf("PHeap start: 0x%x\nPHeap end: 0x%x\n", pheap_begin, pheap_end);
}

// Free a block of memory
void free(void *mem)
{
    alloc_t *alloc = (mem - sizeof(alloc_t));
    memory_used -= alloc->size + sizeof(alloc_t);
    alloc->status = 0;
}

// Free a block of page-aligned memory
void pfree(void *mem)
{
    if(mem < pheap_begin || mem > pheap_end) return;

    // Determine the page ID
    uint32_t ad = (uint32_t)mem;
    ad -= pheap_begin;
    ad /= 4096;

    // Set the page descriptor to free
    pheap_desc[ad] = 0;
}

// Allocate a block of page-aligned memory
char* pmalloc(size_t size)
{
    // Loop through the available list
    for(int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++)
    {
        if(pheap_desc[i]) continue;
        pheap_desc[i] = 1;
        printf("PAllocated from 0x%x to 0x%x\n", pheap_begin + i*4096, pheap_begin + (i+1)*4096);
        return (char *)(pheap_begin + i*4096);
    }
    printf("pmalloc: FATAL: failure!\n");
    return 0;
}


// Allocate a block of memory
void* malloc(size_t size)
{
    if(!size) return 0;

    // Loop through blocks to find an available block with enough size
    uint8_t *mem = (uint8_t *)heap_begin;
    while((uint32_t)mem < last_alloc)
    {
        alloc_t *a = (alloc_t *)mem;
        printf("mem=0x%x a={.status=%d, .size=%d}\n", mem, a->status, a->size);

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
            printf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, mem + sizeof(alloc_t), mem + sizeof(alloc_t) + size);
            memset(mem + sizeof(alloc_t), 0, size);
            memory_used += size + sizeof(alloc_t);
            return (char *)(mem + sizeof(alloc_t));
        }
        // If the block is not allocated and its size is not big enough,
        // add its size and the sizeof(alloc_t) to the pointer and continue.
        mem += a->size;
        mem += sizeof(alloc_t);
        mem += 4;
    }

    nalloc:;
    if(last_alloc + size + sizeof(alloc_t) >= heap_end)
    {
        panic("Cannot allocate bytes! Out of memory.\n");
    }
    alloc_t *alloc = (alloc_t *)last_alloc;
    alloc->status = 1;
    alloc->size = size;

    last_alloc += size;
    last_alloc += sizeof(alloc_t);
    last_alloc += 4;
    printf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), last_alloc);
    memory_used += size + 4 + sizeof(alloc_t);
    memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
    return (char *)((uint32_t)alloc + sizeof(alloc_t));
}
