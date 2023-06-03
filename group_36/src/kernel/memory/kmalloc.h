#include <stdint.h>

uint32_t kmalloc_a(uint32_t sz);  // page aligned.
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys); // returns a physical address.
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys); // page aligned and returns a physical address.
uint32_t kmalloc(uint32_t sz); // vanilla (normal).

void kfree(void *p);

extern "C"{
    extern uint32_t end;
    static uint32_t placement_address = (uint32_t)&end;
}
