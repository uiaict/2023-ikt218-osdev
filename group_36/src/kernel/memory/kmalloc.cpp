#include "kmalloc.h"


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