#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

// Function to map virtual addresses to physical addresses
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);

// Function to enable paging
void paging_enable();

// Function to initialize paging
void init_paging();

#endif /* PAGING_H */