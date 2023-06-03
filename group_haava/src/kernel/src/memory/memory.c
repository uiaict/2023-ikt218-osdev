#include "memory.h"
#include "system.h"

/** Pointer to the page directory, initialized to zero. */
static uint32_t *page_directory = 0;

/** Location of the page directory, initialized to zero. */
static uint32_t page_dir_loc = 0;

/** Pointer to the last page, initialized to zero. */
static uint32_t *last_page = 0;

/** Load the physical page in register CR3, and enable paging with register CR0. */
static void paging_enable()
{
    __asm__ volatile("mov %%eax, %%cr3": :"a"(page_dir_loc));
    __asm__ volatile("mov %cr0, %eax");
    __asm__ volatile("orl $0x80000000, %eax");
    __asm__ volatile("mov %eax, %cr0");
}

/*
 * Paging now will be really simple
 * we reserve 0-8 MB for kernel stuff
 * heap will be from approx 1mb to 4 MB
 * and paging stuff will be from 4 MB
 */

void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
    // Get the upper 10 bits of the virtual address to use as index in the page directory
    uint16_t id = virt >> 22;
    for (int i = 0; i < 1024; i++) {
        // Set the page table entry to the physical address with the present and write permissions set
        last_page[i] = phys | 3;
        // Increment the physical address by the page size of 4 KB
        phys += 4096;
    }
    // Set the page directory entry for the virtual address to the physical
    // address of the page table with present and write permissions set
    page_directory[id] = ((uint32_t) last_page) | 3;
    last_page = (uint32_t *) (((uint32_t) last_page) + 4096); // Move to the next page in memory
}

void paging_init()
{
    printf("Setting up paging\n");
    page_directory = (uint32_t *) 0x400000; /* 4 MB */
    page_dir_loc = (uint32_t) page_directory;
    last_page = (uint32_t *) 0x404000; /* 4 MB + 4 KB */
    for (int i = 0; i < 1024; i++)
        /* Set the page directory entry to not present with
         * supervisor level read/write permissions. */
        page_directory[i] = 0 | 2;
    /* Map the first 4 MB of virtual memory to the first 4 MB of physical memory. */
    paging_map_virtual_to_phys(0, 0);
    /* Map the next 4 MB of virtual memory to the next 4 MB of physical memory. */
    paging_map_virtual_to_phys(0x400000, 0x400000);
    paging_enable();
    printf("Paging was successfully enabled!\n");
}
