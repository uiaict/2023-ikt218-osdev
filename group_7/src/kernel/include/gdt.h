/*
------------------------------------------------------------------------------
This file contains the definitions to implement the  global description table.
------------------------------------------------------------------------------
*/

// the if clause
#ifndef GDT_H
#define GDT_H

#include <stdint.h> // for the uint16_t etc datatypes

/// @brief A struct representing a gdt entry.
struct gdt_entry
{
    /// @brief The 32 bit integer is divided into two 16 bit integeres.
    /// This is the lowest part.
    uint16_t base_low;
    /// @brief the 32 bit integer is divided into two 16 bit integeres.
    /// This is the first 8 bits of the highest part.
    uint8_t base_middle;
    /// @brief the 32 bit integer is divided into two 16 bit integeres.
    /// This is the last 8 bits of the highest part.
    uint8_t base_high;

    /// @brief The address location that accesses the ....
    uint8_t access;
    /// @brief The 16 lowest bit of a limit 32 bit integer.
    uint16_t limit_low;
    /// @brief granularity means the scale or level of detail in a set of data. It is
    /// the highest 16 bits of a 32 bit limit integer.
    uint8_t granularity;
    // NOTE: __attribute__((packed)) make it so the compiler does not
    //      add padding between the fields of the struct.
} __attribute__((packed));

/// @brief A pointer of the limit and base of a gdt entry.
struct gdt_ptr
{
    /// @brief
    uint16_t limit;
    /// @brief The base integer that is divided into base_low, _medium
    /// and _high in the struct.
    uint32_t base;
    //* NOTE: __attribute__((packed)) make it so the compiler does not
    //*      add padding between the fields of the struct.
} __attribute__((packed));

/// @brief Loads the gdt from memory(?).
/// @param gdt_ptr pointer to the pointer struct.
void gdt_load(struct gdt_ptr *gdt_ptr);

/// @brief Creates a gdt entry from the data provided as parameters. Used in init_gdt().
/// @param num the gdt entry number to modify.
/// @param base the base address of the gdt entry.
/// @param limit something
/// @param access something
/// @param gran The granularity
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

/// @brief Initializes the global descriptor table by calling the other functions.
void init_gdt();

#endif /* GDT_H */
