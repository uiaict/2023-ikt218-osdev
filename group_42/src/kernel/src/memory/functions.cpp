#include "functions.h"

extern "C"{
   #include"memory.h"
     void init_kernel();
    
}

#include "memory.h"
#include"../PIT/pit.h"
// start by setting global values who that is not sett to a value at this time
static uint32_t* page_directory = 0;   // pointer to not sett page directory
static uint32_t page_dir_loc = 0;     // location of page directory not sett
static uint32_t* last_page = 0;        // pointer to the last page not sett 


void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)  // function that maps virtual adresses to physical adresses
{
    uint16_t id = virt >> 22;        // get the page id from the virtual adress
    for(int i = 0; i < 1024; i++)  // look att all pages
    {
        last_page[i] = phys | 3;    // sets page entry to to physical adress 
        phys += 4096;              // increment physical adress by page size
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


void init_paging() // function that inizelize paging
{

    page_directory = (uint32_t*)0x400000;    // page directory starts at 4 MB  
    page_dir_loc = (uint32_t)page_directory;  // sets the physical adress of page directory
    last_page = (uint32_t *)0x404000;        // last page starts at 4 MB + 4MB
    for(int i = 0; i < 1024; i++)            // loop through all pages
    {
        page_directory[i] = 0 | 2;           // set the page directory entry to no page
    }
    paging_map_virtual_to_phys(0, 0);       // map first 4 MB of virutal memory to first 4MB of physical
    paging_map_virtual_to_phys(0x400000, 0x400000); // same for the next 4 MB
    paging_enable();                         // asambly fuction in cpp to enable paging
  
}

 extern uint32_t end;
 void init_kernel(){// help function since we for some reason are unable to call the function direcly
   
    init_kernel_memory(&end);
 }

// functions from task 
void* operator new(std::size_t size){ // this function allows creating a new object
    return malloc(size);
}
void* operator new[](std::size_t size){// this function allows creating a new array
    return malloc(size);
} 
void operator delete(void* ptr) noexcept{// this function removing creating a  object
    free(ptr);
}

void operator delete[](void* ptr) noexcept{// this function removing creating a  array
    free(ptr);
}
void init_pag(){// help function since we for some reason are unable to call the function direcly
    init_paging();
}


void start_sleep_busy(uint32_t milliseconds){// help function since we for some reason are unable to call the function direcly
    sleep_busy(milliseconds);
}
