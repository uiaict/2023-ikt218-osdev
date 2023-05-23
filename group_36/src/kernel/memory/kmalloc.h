//
// Created by per on 1/2/23.
//

#ifndef UIAOS_KMALLOC_H
#define UIAOS_KMALLOC_H

#include <stdint.h>

namespace UiAOS::std::Memory{
    uint32_t kmalloc_a(uint32_t sz);  // page aligned.
    uint32_t kmalloc_p(uint32_t sz, uint32_t *phys); // returns a physical address.
    uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys); // page aligned and returns a physical address.
    uint32_t kmalloc(uint32_t sz); // vanilla (normal).

    /**
       General deallocation function.
    **/
    void kfree(void *p);

    // end is defined in the linker script. (link.ld)
    extern "C"{
        extern uint32_t end;
        static uint32_t placement_address = (uint32_t)&end;
    }

}

#endif //UIAOS_KMALLOC_H
