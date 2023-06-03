#include "../include/heap.h"
//#include "system.h"
#include "../include/monitor.h"
#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;


void init_kernel_memory(uint32_t* kernel_end)
{
    last_alloc = kernel_end + 0x1000;                           // kernel end (where the kernel image ends) + 4kb, next available memory address for allocation
    heap_begin = last_alloc;                                    // heap begin is the same as last_alloc
    pheap_end = 0x400000;                                       // page heap end 
    pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096); // page heap begin address
    heap_end = pheap_begin;                                     // kernel heap end address, where page heap begins                                   
    memset((char *)heap_begin, 0, heap_end - heap_begin);       // clear memory withing kernel heap range, set all bytes to 0
    pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);    // set to 0, pointer to page heap descriptor
    monitor_write("Kernel heap starts at ");
    monitor_write_hex(last_alloc);
    monitor_write("\n");
          
}


// Print the current memory layout
void print_memory_layout()
{
    monitor_write("Memory used:");
    monitor_write_dec(memory_used);
    monitor_write("bytes\n");

    monitor_write("Memory free:");
    monitor_write_dec(heap_end - heap_begin - memory_used);
    monitor_write("bytes\n");
    monitor_write("Heap size:");
    monitor_write_dec(heap_end - heap_begin);
    monitor_write("bytes\n");
    monitor_write("Heap start: ");
    monitor_write_hex(heap_begin);
    monitor_write("\n");
    monitor_write("Heap end: ");
    monitor_write_hex(heap_end);
    monitor_write("\n");
    monitor_write("PHeap start: ");
    monitor_write_hex(pheap_begin);
    monitor_write("\nPHeap end: ");
    monitor_write_hex(pheap_end);

    
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
        monitor_write("PAllocated from 0x");
        monitor_write_hex(pheap_begin + i*4096);
        monitor_write(" to 0x");
        monitor_write_hex(pheap_begin + (i+1)*4096);
        monitor_write("\n");
        return (char *)(pheap_begin + i*4096);
    }
    //printf("pmalloc: FATAL: failure!\n");
    monitor_write("pmalloc: FATAL: failure!\n");
    return 0;
}

// Allocate a block of memory
void* malloc(size_t size)
{
    if(!size) return 0;

    // Loop through blocks to find an available block with enough size
    uint8_t *mem = (uint8_t *)heap_begin;
    while((uint32_t)mem < last_alloc)                                     // while the pointer is less than the last allocated address
    {
        alloc_t *a = (alloc_t *)mem;                                     // cast the pointer to alloc_t
        monitor_write("mem=0x");
        monitor_write_hex(mem);
        monitor_write(" a={.status=");
        monitor_write_dec(a->status);
        monitor_write(", .size=");
        monitor_write_dec(a->size);
        monitor_write("}\n");
        

        if(!a->size)                                                    // if the block is not allocated                   
            goto nalloc;                                                  // go to nalloc

        if(a->status)                                                     // if the block is allocated
        {
            mem += a->size + sizeof(alloc_t) + 4;                         // move to the next block
            continue;
        }
        
        
        if(a->size >= size)                                               // if the block is not allocated and its size is big enough
        {
            a->status = 1;                                                // set the status to 1, allocated
            monitor_write("Allocated from: ");
            monitor_write_hex(mem + sizeof(alloc_t));
            monitor_write(" to ");
            monitor_write_hex(mem + sizeof(alloc_t) + size);
            monitor_write("\n");

            
            memset(mem + sizeof(alloc_t), 0, size);                         // clear memory withing the block
            memory_used += size + sizeof(alloc_t);                          // add the size of the block to the memory used
            return (char *)(mem + sizeof(alloc_t));                         // return the location of the block
        }
        
        mem += a->size + sizeof(alloc_t) + 4;                               // if block not allocated and not big enough, add hte size and continue
        
    }

    nalloc:
    /*if(last_alloc + size + sizeof(alloc_t) >= heap_end)
    {
        panic("Cannot allocate bytes! Out of memory.\n");
    }*/
        alloc_t *alloc = (alloc_t *)last_alloc;                              // cast the pointer to alloc_t
        alloc->status = 1;                                                   // set the status to 1, allocated
        alloc->size = size;                                                  // set the size of the block

        last_alloc += size + sizeof(alloc_t) + 4;                                 

        monitor_write("Allocated from ");
        monitor_write_hex((uint32_t)alloc + sizeof(alloc_t));
        monitor_write(" to ");
        monitor_write_hex(last_alloc);
        monitor_write("\n");
        
        memory_used += size + 4 + sizeof(alloc_t);
        memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
        return (char *)((uint32_t)alloc + sizeof(alloc_t));
}