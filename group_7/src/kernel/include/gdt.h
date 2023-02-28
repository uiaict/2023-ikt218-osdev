#ifndef GDT_H
#define GDT_H

#include <stdint.h>
/*
------------------------------------------------------------------------------
This file contains the implementation of the global description table.
------------------------------------------------------------------------------
*/

/// @brief A struct representing a gdt entry.
struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

/// @brief A pointer of the limit and base of a gdt entry.
struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/// @brief Loads the gdt from memory(?).
void gdt_load(struct gdt_ptr *gdt_ptr);

/// @brief Creates a gdt entry from the data provided as parameters. Used in init_gdt().
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

/// @brief Initializes the global descriptor table by calling the other functions.
void init_gdt();

#endif /* GDT_H */
