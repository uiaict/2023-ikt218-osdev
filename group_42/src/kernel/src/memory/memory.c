#include "memory.h"
#include "system.h"

#define MAX_PAGE_ALIGNED_ALLOCS 32
// global varibles we need for fuctionality but dont yet know the value off
uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;


void init_kernel_memory(uint32_t* kernel_end) // function to init kernel memory
{
    last_alloc = kernel_end + 0x1000;
    heap_begin = last_alloc;
    pheap_end = 0x400000;
    pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
    heap_end = pheap_begin;
    memset((char *)heap_begin, 0, heap_end - heap_begin);
    pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);
  
}

 
    


// we have not implimented a print function that works in this file derfore we send all the atributes we want to send to a cpp file
uint32_t get_last_alloc(){
return last_alloc;
}

uint32_t get_heap_end(){
return heap_end;
}
uint32_t get_heap_begin(){
return heap_begin;
}
uint32_t get_pheap_end(){
return pheap_end;
}
uint32_t get_pheap_begin(){
return pheap_begin;
}
uint32_t get_memory_used(){
    return memory_used;
}

void free(void *mem)// this function frees a bloc of memory
{
    alloc_t *alloc = (mem - sizeof(alloc_t));
    memory_used -= alloc->size + sizeof(alloc_t);
    alloc->status = 0;
}

void pfree(void *mem)// this function frees a page of memory
{
    if(mem < pheap_begin || mem > pheap_end) return;

    
    uint32_t ad = (uint32_t)mem; // find page
    ad -= pheap_begin;
    ad /= 4096;

   
    pheap_desc[ad] = 0; // free page
}


char* pmalloc(size_t size) // this function allowcates a paage of memory
{
    
    for(int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++) // find a free page
    {
        if(pheap_desc[i]) continue;
        pheap_desc[i] = 1; // reserve page
       
        return (char *)(pheap_begin + i*4096);// return info
    }
  
    return 0;
}



void* malloc(size_t size)// this function allowcates a block of memory 
{
    if(!size) return 0; // 

    // find available big enough block
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
        // no more bytes inform the user and start a interupt the user can use to stop the program
        asm volatile ("int $0x03");
       
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
