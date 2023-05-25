#include <cstdint>
#include <cstring>
#include <cstdlib>
extern "C" void gdt_flush(uint32_t);
#include "gdt.h"

struct gdtdesc kgdt[GDTSIZE];
struct gdtr kgdtr;

// Initialize GDT segment descriptor
void init_gdt_desc(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdtdesc *desc){

    // Set the descriptor values according to the given parameters
    desc->lim0_15 = (limite & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base16_23 = (uint8_t)((base & 0xff0000) >> 16);
    desc->acces = acces;
    desc->lim16_19 = (uint8_t)((limite & 0xf0000) >> 16);
    desc->other = (uint8_t)(other & 0xf);
    desc->base24_31 = (uint8_t)((base & 0xff000000) >> 24);
    return;
}

// Initialize the GDT
void init_gdt(void){

    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);    // Code
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);    // Data
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);        // Stack

    init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]);    // ucode
    init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]);    // udata
    init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]);        // ustack

    // Initializegdtr
    kgdtr.limite = GDTSIZE * 8;
    kgdtr.base = GDTBASE;

    // Copy the gdtr to its memory position
    for (size_t i = 0; i < GDTSIZE; i++) {
        ((struct gdtdesc *)kgdtr.base)[i] = kgdt[i];
    }

    gdt_flush((uint32_t)&kgdtr);
}