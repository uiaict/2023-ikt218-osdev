#include <memory.h>
#include <stdint.h>          // Include the standard integer types
#include <stddef.h>          // Include the standard size types
#include <terminal.h> 
#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t *pheap_desc = 0;
uint32_t memory_used = 0;
uint32_t page_dir_loc =0;
uint32_t* page_directory=0;
uint32_t* last_page=0;

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
    terminal_writestring("Kernel heap starts at 0x");
    terminal_write_dec(last_alloc);
    terminal_writestring("\n");

}


void paging_enable()
{
    asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc)); // Load the physical address of the page directory into the CR3 register
    asm volatile("mov %cr0, %eax");         // Load the CR0 register into the EAX register
    asm volatile("orl $0x80000000, %eax");  // Set the paging enable bit in the EAX register
    asm volatile("mov %eax, %cr0");         // Load the EAX register into the CR0 register to enable paging
}
// Function to initialize paging
void init_paging()
{
    terminal_writestring("Setting up paging\n");
    page_directory = (uint32_t*)0x400000;      // Set the page directory to start at 4 MB
    page_dir_loc = (uint32_t)page_directory;  // Set the physical address of the page directory
    last_page = (uint32_t *)0x404000;         // Set the last page to start at 4 MB + 4 KB
    for(int i = 0; i < 1024; i++)             // Loop through all 1024 page directory entries
    {
        page_directory[i] = 0 | 2;            // Set the page directory entry to not present with supervisor level read/writesting permissions
    }
    paging_map_virtual_to_phys(0, 0);         // Map the first 4 MB of virtual memory to the first 4 MB of physical memory
    paging_map_virtual_to_phys(0x400000, 0x400000); // Map the next 4 MB of virtual memory to the next 4 MB of physical memory
    paging_enable();                          // Enable paging
    terminal_writestring("Paging was successfully enabled!\n");
}
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
    uint16_t id = virt >> 22;        // Get the upper 10 bits of the virtual address to use as index in the page directory
    for(int i = 0; i < 1024; i++)   // Loop through all 1024 page table entries
    {
        last_page[i] = phys | 3;    // Set the page table entry to the physical address with the present and writesting permissions set
        phys += 4096;               // Increment the physical address by the page size of 4 KB
    }
    page_directory[id] = ((uint32_t)last_page) | 3;  // Set the page directory entry for the virtual address to the physical address of the page table with present and writesting permissions set
    last_page = (uint32_t *)(((uint32_t)last_page) + 4096); // Move to the next page in memory
}

extern "C" char* pmalloc(size_t size)
{
    // Loop through the available list
    for(int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++)
    {
        if(pheap_desc[i]) continue;
        pheap_desc[i] = 1;
        //printf("PAllocated from 0x%x to 0x%x\n", pheap_begin + i*4096, pheap_begin + (i+1)*4096);
        terminal_writestring("PAllocated from 0x");
        terminal_write_dec( pheap_begin + i*4096);
        terminal_writestring("to 0x");
        terminal_write_dec( pheap_begin + (i+1)*4096);
        terminal_writestring("\n");
        return (char *)(pheap_begin + i*4096);
    }
    terminal_writestring("pmalloc: FATAL: failure!\n");
    return 0;
}

extern "C" void* malloc(size_t size)
{
    
    if(!size) return 0;

    // Loop through blocks to find an available block with enough size
    uint8_t *mem = (uint8_t *)heap_begin;
    while((uint32_t)mem < last_alloc)
    {
        alloc_t *a = (alloc_t *)mem;
        // printf("mem=0x%x a={.status=%d, .size=%d}\n", mem, a->status, a->size);
          terminal_writestring("mem=0x");
          terminal_write_dec(mem);
          terminal_writestring(", a={.status=");
          terminal_write_dec(a->status);
          terminal_writestring(",  .size=");
          terminal_write_dec(a->size);
          terminal_writestring("}\n");

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
            //printf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, mem + sizeof(alloc_t), mem + sizeof(alloc_t) + size);
            terminal_writestring("RE:Allocated");
            terminal_write_dec( size);
            terminal_writestring("from");
            terminal_write_dec( mem + sizeof(alloc_t));
            terminal_writestring("to 0x");
            terminal_write_dec( mem + sizeof(alloc_t) + size);
            terminal_writestring("\n");
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
        //panic("Cannot allocate bytes! Out of memory.\n");
        terminal_writestring("Cannot allocate bytes! Out of memory.\n");
    }
    alloc_t *alloc = (alloc_t *)last_alloc;
    alloc->status = 1;
    alloc->size = size;

    last_alloc += size;
    last_alloc += sizeof(alloc_t);
    last_alloc += 4;
    // printf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), last_alloc);
    terminal_writestring("Allocated ");
    terminal_write_dec(size);
    terminal_writestring(" bytes from 0x");
    terminal_write_dec( (uint32_t)alloc + sizeof(alloc_t));
    terminal_writestring(" to 0x");
    terminal_write_dec( last_alloc);
    terminal_writestring("\n");
    memory_used += size + 4 + sizeof(alloc_t);
    memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
    return (char *)((uint32_t)alloc + sizeof(alloc_t));
}

extern "C" void free(void *mem)
{
    alloc_t *alloc = (mem - sizeof(alloc_t));

    memory_used -= alloc->size + sizeof(alloc_t);
    alloc->status = 0;
}

extern "C" void* memcpy(void* dest, const void* src, size_t count )
{
    char* dst8 = (char*)dest;  // Cast the destination pointer to char*
    char* src8 = (char*)src;   // Cast the source pointer to char*

    if (count & 1) {           // If the count is odd
        dst8[0] = src8[0];     // Copy one byte from source to destination
        dst8 += 1;             // Increment destination pointer by one byte
        src8 += 1;             // Increment source pointer by one byte
    }

    count /= 2;                // Divide the count by two to copy 2 bytes at a time
    while (count--) {          // Loop through each pair of 2 bytes
        dst8[0] = src8[0];     // Copy the first byte of the pair from source to destination
        dst8[1] = src8[1];     // Copy the second byte of the pair from source to destination

        dst8 += 2;             // Increment destination pointer by 2 bytes
        src8 += 2;             // Increment source pointer by 2 bytes
    }

    return (void*)dest;        // Return the destination pointer
}


// Function to set a block of memory with a byte value
extern "C" void* memset (void * ptr, int value, size_t num )
{
    unsigned char* p=ptr;     // Cast the pointer to unsigned char*
    while(num--)
        *p++ = (unsigned char)value;   // Set each byte to the given value
    return ptr;               // Return the pointer to the block of memory
}
//comment
// Function to set a block of memory with a 16-bit value
extern "C" void* memset16 (void *ptr, uint16_t value, size_t num)
{
    uint16_t* p = ptr;        // Cast the pointer to uint16_t*
    while(num--)
        *p++ = value;         // Set each 2-byte element to the given value
    return ptr;               // Return the pointer to the block of memory
}

void print_memory_layout()
{
   
    terminal_writestring("Memory used: ");
    terminal_write_dec(memory_used);
    terminal_writestring(" bytes \n");
   
    terminal_writestring("Memory free ");
    terminal_write_dec( heap_end - heap_begin - memory_used);
    terminal_writestring(" bytes \n");

    terminal_writestring("Heap size ");
    terminal_write_dec( heap_end - heap_begin);
    terminal_writestring(" bytes \n");
   
    terminal_writestring("Heap start: 0x");
    terminal_write_dec(heap_begin);
    terminal_writestring("\n");

    terminal_writestring("Heap end: 0x");
    terminal_write_dec(heap_end);
    terminal_writestring(" \n");
  
    terminal_writestring("PHeap start: 0x");
    terminal_write_dec(pheap_begin);
    terminal_writestring(" \n");

    terminal_writestring("PHeap end: 0x");
    terminal_write_dec(pheap_end);
    terminal_writestring(" \n");
    
    
}
