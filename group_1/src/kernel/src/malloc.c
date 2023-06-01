


#include "memory.h"
#include <stdint.h>
#include "system.h"
#include "common.h"
#include "panic.h"


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
    pheap_desc = (uint8_t *)new_malloc(MAX_PAGE_ALIGNED_ALLOCS);
    printk("Kernel heap starts at 0x%x\n", last_alloc);
}

// Print the current memory layout
void print_memory_layout()
{
    //int memoryUsed = memory_used;
    printk("Memory used: %d bytes\n", memory_used);
    printk("Memory free: %d bytes\n", heap_end - heap_begin - memory_used);
    printk("Heap size: %d bytes\n", heap_end - heap_begin);
    printk("Heap start: 0x%x\n", heap_begin);
    printk("Heap end: 0x%x\n", heap_end);
    printk("PHeap start: 0x%x\nPHeap end: 0x%x\n", pheap_begin, pheap_end);
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
char* pmalloc(size_t _size)
{
    // Loop through the available list
    for(int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++)
    {
        if(pheap_desc[i]) continue;
        pheap_desc[i] = 1;
        printk("PAllocated from 0x%x to 0x%x\n", pheap_begin + i*4096, pheap_begin + (i+1)*4096);
        return (char *)(pheap_begin + i*4096);
    }
    printk("pmalloc: FATAL: failure!\n");
    return 0;
}


// Allocate a block of memory
void* new_malloc(size_t size)
{
    if(!size) return 0; // If the size is 0, return 0

    // Loop through blocks to find an available block with enough size
    uint8_t *mem = (uint8_t *)heap_begin; // Start at the beginning of the heap
    while((uint32_t)mem < last_alloc) // 
    {
        alloc_t *a = (alloc_t *)mem; // Get the allocation header
        printk("mem=0x%x a={.status=%d, .size=%d}\n", mem, a->status, a->size); // Print the allocation header

        if(!a->size) // If the size is 0, the heap is empty, so goto nalloc. This means that the heap is empty.
            goto nalloc; 
        if(a->status) { // If the block is allocated, skip it
            mem += a->size; // Add the size of the block to the pointer
            mem += sizeof(alloc_t); // Add the size of the allocation header to the pointer
            mem += 4; // Add 4 bytes to the pointer because of the 4-byte alignment of the heap (I think)
            continue; 
        }

        // If the block is not allocated and its size is big enough,
        // adjust its size, set the status, and return the location.
        if(a->size >= size) // If the size of the block is big enough, allocate it 
        {
            a->status = 1; // Set the status to allocated
            printk("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, mem + sizeof(alloc_t), mem + sizeof(alloc_t) + size); // Print the allocation
            memset(mem + sizeof(alloc_t), 0, size); // Set the memory to 0
            memory_used += size + sizeof(alloc_t); // Add the size of the allocation header and the size of the block to the memory used
            return (char *)(mem + sizeof(alloc_t)); // Return the location of the block
        }
        // If the block is not allocated and its size is not big enough,
        // add its size and the sizeof(alloc_t) to the pointer and continue.
        mem += a->size; // Add the size of the block to the pointer
        mem += sizeof(alloc_t); // Add the size of the allocation header to the pointer
        mem += 4; // Add 4 bytes to the pointer because of the 4-byte alignment of the heap (I think)
    }

    nalloc:;
    if(last_alloc + size + sizeof(alloc_t) >= heap_end) // If the size of the block is too big
    {
        PANIC("Cannot allocate bytes! Out of memory.\n");
    }
    alloc_t *alloc = (alloc_t *)last_alloc; // Get the allocation header of the block to allocate 
    alloc->status = 1; // Set the status to allocated
    alloc->size = size; // Set the size of the block

    last_alloc += size; // Add the size of the block to the pointer
    last_alloc += sizeof(alloc_t); // Add the size of the allocation header to the pointer
    last_alloc += 4; // Add 4 bytes to the pointer because of the 4-byte alignment of the heap (I think)
    printk("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), last_alloc); // Print the allocation
    memory_used += size + 4 + sizeof(alloc_t); // Add the size of the allocation header and the size of the block to the memory used
    memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size); // Set the memory to 0
    return (char *)((uint32_t)alloc + sizeof(alloc_t)); // Return the location of the block
}
