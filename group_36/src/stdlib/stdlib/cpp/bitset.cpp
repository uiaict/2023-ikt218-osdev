//
// Created by per on 1/2/23.
//
#include "bitset.h"
#include "memory.h"

namespace UiAOS::std::Memory{
    extern uint32_t kmalloc(uint32_t);
}


using namespace UiAOS::std;

void Bitset::set_frame(uint32_t frame) {
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

uint32_t Bitset::first_available_frame() {
    uint32_t i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            // at least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                uint32_t toTest = 0x1 << j;
                if ( !(frames[i]&toTest) )
                {
                    return i*4*8+j;
                }
            }
        }
    }
}

Bitset::Bitset(uint32_t _mem_end_page, uint32_t _n_frames)
        : mem_end_page(_mem_end_page)
        , nframes(_n_frames)
{
    frames = (uint32_t*)UiAOS::std::Memory::kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));
}

uint32_t Bitset::test_frame(uint32_t frame) {
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

void Bitset::clear_frame(uint32_t frame) {
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}
