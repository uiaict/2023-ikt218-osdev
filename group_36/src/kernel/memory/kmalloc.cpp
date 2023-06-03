#include "kmalloc.h"

// Keep track of each memory block's information
struct BlockHeader {
    // The size of this block
    uint32_t size;
    // Whether this block is in use
    bool inUse;
};

uint32_t kmalloc_internal(uint32_t sz, int align, uint32_t *phys)
{
    if (align == 1 && (placement_address & 0x00000FFF))
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

// uint32_t kmalloc_internal(uint32_t sz, int align, uint32_t *phys) {
//     if (align == 1 && (placement_address & 0x00000FFF))
//     {
//         // Align the placement address;
//         placement_address &= 0xFFFFF000;
//         placement_address += 0x1000;
//     }

//     if (phys) {
//         *phys = placement_address;
//     }

//     // Keep track of the original placement address
//     uint32_t original = placement_address;
//     // Increment the placement address by the size of the block header
//     placement_address += sizeof(BlockHeader);
//     // Set up the block header
//     BlockHeader *header = (BlockHeader *)placement_address;
//     header->size = sz;
//     header->inUse = true;
//     // Increment the placement address by the requested size
//     placement_address += sz;

//     // Return the address of the block header
//     return original;
// }


void kfree(void *ptr) {
    // Get the block header for this pointer
    BlockHeader *header = (BlockHeader *)((uint32_t)ptr - sizeof(BlockHeader));
    // Mark the block as not in use
    header->inUse = false;
    // Ideally, you should now merge this free block with any adjacent free blocks
}


uint32_t kmalloc_a(uint32_t sz)
{
    return kmalloc_internal(sz, 1, 0);
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
    return kmalloc_internal(sz, 0, phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
    return kmalloc_internal(sz, 1, phys);
}

uint32_t kmalloc(uint32_t sz)
{
    return kmalloc_internal(sz, 0, nullptr);
}