//
// Created by per on 1/2/23.
//

#ifndef UIAOS_BITSET_H
#define UIAOS_BITSET_H

#include <stdint.h>

// Macros used in the bitset algorithm
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

namespace UiAOS::std{
    class Bitset{
        uint32_t *frames;
        uint32_t nframes;
        uint32_t mem_end_page;


        // Static function to clear a bit in the frames bitset
        void clear_frame(uint32_t frame);

        // Static function to test if a bit is set.
        uint32_t test_frame(uint32_t frame);


    public:
        Bitset(uint32_t _mem_end_page, uint32_t _n_frames);

        // Static function to find the first free frame.
        uint32_t first_available_frame();

        // Static function to set a bit in the frames bitset
        void set_frame(uint32_t frame);
    };


}



#endif //UIAOS_BITSET_H
