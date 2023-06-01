#ifndef PAGING_H
#define PAGING_H

/* Function declarations for paging operations */
extern void init_paging(); /* Initializes paging */
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); /* Maps a virtual address to a physical address */

#endif