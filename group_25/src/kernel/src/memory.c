#include "memory.h"
#include <system.h>

// Define pointer to page directory
static uint32_t* page_directory = 0;
// Define location of page directory
static uint32_t page_dir_loc = 0;
// Define pointer to the last page
static uint32_t* last_page = 0;

// Function to initialize paging
void init_paging(){
    printf("Begging to set up paging\n");
    page_directory = (uint32_t*)0x400000;      // Set the page directory to start at 4 MB
    page_dir_loc = (uint32_t)page_directory;  // Set the physical address of the page directory
    last_page = (uint32_t *)0x404000;         // Set the last page to start at 4 MB + 4 KB
    for(int i = 0; i < 1024; i++){
        page_directory[i] = 0 | 2;            // Set the page directory entry to not present with supervisor level read/write permissions
    }
    paging_map_virtual_to_phys(0, 0);         // Map the first 4 MB of virtual memory to the first 4 MB of physical memory
    paging_map_virtual_to_phys(0x400000, 0x400000); // Map the next 4 MB of virtual memory to the next 4 MB of physical memory
    paging_enable();                          // Enable paging
    printf("Completed setting up paging\n");
}

// Function to map virtual addresses to physical addresses
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys){
    uint16_t id = virt >> 22;
    for(int i = 0; i < 1024; i++){
        last_page[i] = phys | 3;
        phys += 4096;
    }
    page_directory[id] = ((uint32_t)last_page) | 3;
    last_page = (uint32_t *)(((uint32_t)last_page) + 4096);
}

// Enable paging
void paging_enable(){
    asm volatile("mov %%eax, %%cr3": :"a"(page_dir_loc)); // Load the physical address of the page directory into the CR3 register
    asm volatile("mov %cr0, %eax");         // Load the CR0 register into the EAX register
    asm volatile("orl $0x80000000, %eax");  // Set the paging enable bit in the EAX register
    asm volatile("mov %eax, %cr0");         // Load the EAX register into the CR0 register to enable paging
}