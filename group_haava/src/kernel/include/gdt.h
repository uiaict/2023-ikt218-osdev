/**
 * @file
 * @brief Global Descriptor Table (GDT).
 *
 * Structures and public functions needed to create and initialize GDT described
 * in Intel's manual "Intel 64 and IA-32 Architectures Developer's Manual: Vol. 3A".
 * If in doubt, reference this manual.
 */

#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Entries in GDT table. */
#define GDT_ENTRIES 3


/**
 * @brief Segment descriptor
 *
 * A segment descriptor is a data structure in a GDT or LDT that provides the
 * processor with the size and location of a segment, as well as access control
 * and status information.
 *
 * The base address should be aligned to 16-byte boundaries, to maximize
 * performance.
 */
struct gdt_entry {
    uint16_t limit_low;     /*!< Specifies size of the segment, lower part. */
    uint16_t base_low;      /*!< Location of byte 0 of the segment within the
                                 4-GByte linear address space, lower part. */
    uint8_t base_middle;    /*!< Location of byte 0 of the segment within the
                                 4-GByte linear address space, middle part. */
    uint8_t access;         /*!< Sets flags 'P', 'DPL', 'S' and 'Type' that
                                 consist of 'E', 'DC', 'RW' and 'A'. */
    uint8_t granularity;    /*!< Sets flags 'G', 'D/B', 'L', 'AVL' and the upper
                                 part of the segment limit field. */
    uint8_t base_high;      /*!< Location of byte 0 of the segment within the
                                 4-GByte linear address space, upper part. */
} __attribute__((packed));

/** @brief Holds information about the GDT.
 *
 * This struct is used in assembly by the instruction @c lgdt. It is only valid
 * in compat/legacy mode. The instruction expects the struct to have this
 * specific size and variables in the current order.
 */
struct gdt_ptr {
    uint16_t limit; /*!< Size of GDT in bytes */
    uint32_t base;  /*!< Memory location of the GDT */
} __attribute__((packed));

/**
 * @brief Initialize GDT.
 *
 * For now we only initialize the NULL, code and data segment.
 */
void gdt_init();


#ifdef __cplusplus
};
#endif

#endif /* KERNEL_GDT_H */
