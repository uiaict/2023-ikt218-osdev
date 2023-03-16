/*
------------------------------------------------------------------------------
This file contains the definitions to implement the  global description table.
------------------------------------------------------------------------------
*/

// the if clause
#ifndef GDT_H
#define GDT_H

#include <stdint.h> // for the uint16_t etc datatypes

/// @brief Number of entries in the global description table
#define GDT_ENTRIES 5


/// @brief A struct representing a gdt entry.
struct gdt_entry
{
    /// @brief The 16 lowest bit of a limit 32 bit integer. 
    /// The limit is the address of the last available address of the gdt.
    uint16_t limit_low;
    /// @brief The 32 bit integer is divided into two 16 bit integeres.
    /// This is the lowest part.
    uint16_t base_low;
    /// @brief the 32 bit integer is divided into two 16 bit integeres.
    /// This is the first 8 bits of the highest part.
    uint8_t base_middle;

    /// @brief The access level for this part of the memory.
    uint8_t access;
    /// @brief granularity means the scale or level of detail in a set of data.
    uint8_t granularity;
    /// @brief the 32 bit integer is divided into two 16 bit integeres.
    /// This is the last 8 bits of the highest part.
    uint8_t base_high;
    // NOTE: __attribute__((packed)) make it so the compiler does not
    //      add padding between the fields of the struct.
} __attribute__((packed));

/// @brief A pointer of the limit and base of a gdt entry.
struct gdt_ptr
{
    /// @brief The address of the last entry in the gdt table.
    uint16_t limit;
    /// @brief The base integer that is divided into base_low, _medium
    /// and _high in the struct.
    uint32_t base;
    //* NOTE: __attribute__((packed)) make it so the compiler does not
    //*      add padding between the fields of the struct.
} __attribute__((packed));


/// @brief Creates a gdt entry from the data provided as parameters. Used in init_gdt().
/// @param num the gdt entry number to modify.
/// @param base the base address of the gdt entry.
/// @param limit The last address the gdt table has access to.
/// @param access something
/// @param gran The granularity
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

/// @brief Initializes the global descriptor table by calling the other functions from gdt.h and gdt.cpp
void init_gdt();


/// @brief  the global description table array.
static gdt_entry gdt[GDT_ENTRIES];
/// @brief Pointer to the global description table.
static gdt_ptr gdt_ptr;

#endif /* GDT_H */
