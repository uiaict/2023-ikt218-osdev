#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#include <stdint.h> 
#include "common.h"

#define GDT_ENTRIES 5
#define IDT_ENTRIES 256


struct gdt_entry_t
{
    uint16_t low_limit;
    uint16_t low_base;
    uint8_t mid_base;
    uint8_t access; 
    uint8_t granularity; 
    uint8_t high_base;
}__attribute__((packed));

struct idt_entry_t
{
    uint16_t selector;
    uint16_t low_base;
    uint8_t flags;
    uint8_t zero;  
    uint16_t high_base;
}__attribute__((packed));

struct gdt_ptr_t
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct idt_ptr_t
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct int_handler {
    void (*handler)(void *data);
    int num;
    void *data; 
};


void init_idt();
void idt_load(struct idt_ptr *idt_ptr);


void init_gdt();
void gdt_load(struct gdt_ptr_t *gdt_ptr);
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif