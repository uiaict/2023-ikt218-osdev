#include "functions.h"

extern "C"{
   #include"memory.h"
     void init_kernel();
    
}

#include "memory.h"
#include"../PIT/pit.h"
// start by setting global values that initially do not have a value
static uint32_t* page_directory = 0;   // pointer to page directory
static uint32_t page_dir_loc = 0;     // location of page directory
static uint32_t* last_page = 0;        // pointer to the last page 


void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)  // function that maps virtual addresses to physical addresses
{
    uint16_t id = virt >> 22;        // get the page id from the virtual address' 10 leftmost bits
    for(int i = 0; i < 1024; i++)  // loop through all entries
    {
        last_page[i] = phys | 3;    // sets page entry to to physical address, ensure last two bits are set to 1
        phys += 4096;              // increment physical address by page size
    } 
    page_directory[id] = ((uint32_t)last_page) | 3;  
    last_page = (uint32_t *)(((uint32_t)last_page) + 4096); // move to next page
}

void paging_enable() // function to enable paging
{
    asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc)); 
    asm volatile("mov %cr0, %eax");         
    asm volatile("orl $0x80000000, %eax"); 
    asm volatile("mov %eax, %cr0");         
}


void init_paging() // function that initialize paging
{

    page_directory = (uint32_t*)0x400000;    // page directory starts at 4 MB  
    page_dir_loc = (uint32_t)page_directory;  // sets the physical address of page directory
    last_page = (uint32_t *)0x404000;        // last page starts at 4 MB + 4KB
    for(int i = 0; i < 1024; i++)            // loop through all pages
    {
        page_directory[i] = 0 | 2;           // set the page directory entry's bits to 0 except for read/write bit
    }
    paging_map_virtual_to_phys(0, 0);       // map first 4 MB of virtual memory to first 4MB of physical memory
    paging_map_virtual_to_phys(0x400000, 0x400000); // same for the next 4 MB
    paging_enable();                         // assembly fuction in cpp to enable paging
  
}

 extern uint32_t end;
 void init_kernel(){// wrapper function since we for some reason are unable to call the function directly in boot.asm
   
    init_kernel_memory(&end);
 }

// functions from task 
void* operator new(std::size_t size){ // this operator allows for creating a new variable or object
    return malloc(size);
}
void* operator new[](std::size_t size){// this operator allows for creating a new array
    return malloc(size);
} 
void operator delete(void* ptr) noexcept{// this operator allows for removing a variable or object from memory
    free(ptr);
}

void operator delete[](void* ptr) noexcept{// this operator allows for removing an array from memory
    free(ptr);
}
void init_pag(){// wrapper function since we for some reason are unable to call the function directly in kernel_main
    init_paging();
}


void start_sleep_busy(uint32_t milliseconds){// wrapper function since we for some reason are unable to call the function directly
    sleep_busy(milliseconds);
}
