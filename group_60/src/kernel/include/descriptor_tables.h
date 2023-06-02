#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H
#include <stdint.h>

#define GDT_ENTRIES 5
#define IDT_ENTRIES 256

typedef struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr;

typedef struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry;


typedef struct idt_ptr {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idt_ptr;

typedef struct idt_entry {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry;



void init_gdt();
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

/* Our GDT, with 5 entries, and finally our GDT pointer */
static gdt_entry gdt[GDT_ENTRIES];
static gdt_ptr gdt_p;

/* Our IDT, with 256 entries, and finally our IDT pointer */
void init_idt();
void load_idt();
/* We dont include:
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
because it is never used outside of "idt.cpp", if needed can be moved out of comment */
static idt_entry idt[IDT_ENTRIES];
static idt_ptr idt_p;

#endif