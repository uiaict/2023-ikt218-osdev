#include "kernel/memory.h"


// Initialize a page entry
void init_page_entry(page_entry_t* entry, uintptr_t base_addr, int present, int rw, int us) {
    entry->present   = present;
    entry->rw        = rw;
    entry->us        = us;
    entry->pwt       = 0;
    entry->pcd       = 0;
    entry->accessed  = 0;
    entry->dirty     = 0;
    entry->pat       = 0;
    entry->global    = 0;
    entry->available = 0;
    entry->base_addr = base_addr >> 12;
}


void init_paging() {
    // Set up identity mapping for the first 4 MiB of memory
    for (size_t i = 0; i < PAGE_DIR_ENTRY_COUNT; i++) {
        init_page_entry(&page_directory[i], (uintptr_t)page_tables[i], 1, 1, 0);
        for (size_t j = 0; j < PAGE_TABLE_ENTRY_COUNT; j++) {
            uintptr_t base_addr = (i * PAGE_TABLE_ENTRY_COUNT + j) * PAGE_SIZE;
            init_page_entry(&page_tables[i][j], base_addr, 1, 1, 0);
        }
    }

    // Load the page directory base address into the CR3 register
    asm volatile (
        "mov %0, %%cr3"
        : /* no output */
        : "r" (page_directory)
    );

    // Enable paging by setting the PG and PE bits in the CR0 register
    uint32_t cr0;
    asm volatile (
        "mov %%cr0, %0"
        : "=r" (cr0)
    );
    cr0 |= (1 << 31) | (1 << 0);
    asm volatile (
        "mov %0, %%cr0"
        : /* no output */
        : "r" (cr0)
    );
}