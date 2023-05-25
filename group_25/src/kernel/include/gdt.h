#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDTBASE 0x00000800
#define GDTSIZE 8

struct gdtdesc {
    uint16_t lim0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t acces;
    uint8_t lim16_19:4;
    uint8_t other:4;
    uint8_t base24_31;
} __attribute__((packed));

struct gdtr {
    uint16_t limite;
    uint32_t base;
} __attribute__((packed));


void init_gdt(void);
void init_gdt_desc(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdtdesc *desc);

#endif