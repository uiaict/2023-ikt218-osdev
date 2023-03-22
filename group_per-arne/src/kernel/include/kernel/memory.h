#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define PAGE_DIR_ENTRY_COUNT 1024
#define PAGE_TABLE_ENTRY_COUNT 1024

// Align address to the nearest lower 4KiB boundary
#define ALIGN_DOWN(addr) ((uintptr_t)(addr) & ~(PAGE_SIZE - 1))

// Page directory and table entries
typedef struct {
    uint32_t present    : 1;
    uint32_t rw         : 1;
    uint32_t us         : 1;
    uint32_t pwt        : 1;
    uint32_t pcd        : 1;
    uint32_t accessed   : 1;
    uint32_t dirty      : 1;
    uint32_t pat        : 1;
    uint32_t global     : 1;
    uint32_t available  : 3;
    uint32_t base_addr  : 20;
} __attribute__((packed)) page_entry_t;


// Page directory and tables
static page_entry_t page_directory[PAGE_DIR_ENTRY_COUNT] __attribute__((aligned(PAGE_SIZE)));
static page_entry_t page_tables[PAGE_DIR_ENTRY_COUNT][PAGE_TABLE_ENTRY_COUNT] __attribute__((aligned(PAGE_SIZE)));

void init_page_entry(page_entry_t* entry, uintptr_t base_addr, int present, int rw, int us);

void init_paging();


#endif