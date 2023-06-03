/**
 * @file
 * @brief Interrupt Descriptor Table (IDT).
 *
 * Structures and public functions needed to create and initialize IDT described
 * in Intel's manual "Intel 64 and IA-32 Architectures Developer's Manual: Vol. 3A".
 * If in doubt, reference this manual.
 */

#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Entries in IDT table. */
#define IDT_ENTRIES 256

/**
 * @brief IDT gate descriptor
 *
 * The IDT can be used to create three kinds of gate descriptors:
 * <ul>
 * <li> Task-gate descriptor
 * <li> Interrupt-gate descriptor
 * <li> Trap-gate descriptor
 * </ul>
 */
struct idt_entry {
    uint16_t offset_low;     /*!< Specifies size of the offset, lower part. */
    uint16_t selector;       /*!< Segment selector, must point to a valid code
                                  code segment in GDT. */
    uint8_t zero;            /*!< Reserved, always zero */
    uint8_t attributes;      /*!< Set flags 'P', 'DPL', and 'gate type'. */
    uint16_t offset_high;    /*!< Specifies size of the offset, upper part. */
};

/**
 * @brief IDT descriptor.
 *
 * This struct is used in assembly by the instruction @c lidt. It is only valid
 * in compat/legacy mode. The instruction expects the struct to have this
 * specific size and variables in the current order.
 */
struct idt_ptr {
    uint16_t limit; /*!< Size of IDT in bytes */
    uint32_t base;  /*!< Memory location of the IDT */
} __attribute__((packed));


#ifdef __cplusplus
};
#endif

#endif /* KERNEL_IDT_H */
