#include <stdint.h>
#include "paging.h"

// A bitset of frames - used or free.
uint32_t *frames;
uint32_t nframes;

// Defined in kheap.c
extern uint32_t placement_address;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset
static void set_frame(uint32_t frame_addr);

// Static function to clear a bit in the frames bitset
static void clear_frame(uint32_t frame_addr);


// Static function to test if a bit is set.
static uint32_t test_frame(uint32_t frame_addr);

// Static function to find the first free frame.
static uint32_t first_frame();

// Function to allocate a frame.
void alloc_frame(page_t *page, int is_kernel, int is_writeable);

// Function to deallocate a frame.
void free_frame(page_t *page);