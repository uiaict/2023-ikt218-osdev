#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "monitor.h"
#include "isr.h"

typedef struct page
{
   u32int present    : 1;   // Page present in memory
   u32int rw         : 1;   // Read-only if clear, readwrite if set
   u32int user       : 1;   // Supervisor level only if clear
   u32int accessed   : 1;   // Has the page been accessed since last refresh?
   u32int dirty      : 1;   // Has the page been written to since last refresh?
   u32int unused     : 7;   // Amalgamation of unused and reserved bits
   u32int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
   page_table_t *tables[1024];
   u32int tablesPhysical[1024];
   u32int physicalAddr;
} page_directory_t;

void initialise_paging();
void switch_page_directory(page_directory_t *new_directory);
page_t *get_page(u32int address, int make, page_directory_t *dir);
void page_fault(registers_t regs); 
u32int kmalloc_a(u32int sz);  // page aligned.
u32int kmalloc_p(u32int sz, u32int *phys); // returns a physical address.
u32int kmalloc_ap(u32int sz, u32int *phys); // page aligned and returns a physical address.
u32int kmalloc(u32int sz, int align, u32int *phys); // vanilla (normal). 
extern page_directory_t* kernel_directory;
extern page_directory_t* current_directory;
extern u32int placement_address;



#endif