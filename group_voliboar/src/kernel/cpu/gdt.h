#ifndef VOLI_GDT_H
#define VOLI_GDT_H
#include <stdint.h>

namespace VOLI::CPU::GDT{

        // This structure contains the value of one GDT entry.
        // We use the attribute 'packed' to tell GCC not to change
        // any of the alignment in the structure.
        struct gdt_entry_struct
        {
            uint16_t limit_low;           // The lower 16 bits of the limit.
            uint16_t base_low;            // The lower 16 bits of the base.
            uint8_t  base_middle;         // The next 8 bits of the base.
            uint8_t  access;              // Access flags, determine what ring this segment can be used in.
            uint8_t  granularity;
            uint8_t  base_high;           // The last 8 bits of the base.
        };

        typedef struct gdt_entry_struct gdt_entry_t;

        // This struct describes a GDT pointer. It points to the start of
        // our array of GDT entries, and is in the format required by the
        // lgdt instruction.
        struct gdt_ptr_struct
        {
            uint16_t limit;               // The upper 16 bits of all selector limits.
            uint32_t base;                // The address of the first gdt_entry_t struct.
        } __attribute__((packed));

        typedef struct gdt_ptr_struct gdt_ptr_t;

        // Function definitions
        void init_gdt();
        void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
}

#endif //VOLI_GDT_H

// SOURCE:
// # https://github.com/perara/ikt218-advanced-operating-systems/blob/master/src/kernel/cpu/i386/gdt.h