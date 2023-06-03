#include <cstdint>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

class GDT {
    public:
        static void init();
        static gdt_entry gdt_entries[3];
        static gdt_pointer gdt_ptr;
};