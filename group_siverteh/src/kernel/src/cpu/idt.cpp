#include "idt.h"

extern "C" {
    extern void idt_flush(uint32_t idt_ptr);
}

//Sets up instances of the idt_entry struct, and idt_ptr struct.
struct idt_entry idt_entries[IDT_ENTRIES];
struct idt_ptr   idt_ptr;

void load_idt()
{
   idt_ptr.limit = sizeof(idt_entry) * IDT_ENTRIES - 1;
   idt_ptr.base = (uint32_t)&idt_entries;

   //Code note finished
   //idt_flush((uint32_t)&idt_ptr)
}

//Set the value of one IDT entry.
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    //These two lines sets the base address of the segment.
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    //Sets the value of the sel and always0 fields.
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;

    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags = flags /* | 0x60*/;
}