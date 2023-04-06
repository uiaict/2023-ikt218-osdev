#include "common.h"

extern "C" {
    extern void init_idt();
    extern void idt_flush(uint32_t);
}

// A struct describing an interrupt gate.
struct idt_entry_struct
{
   u16int base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   u16int sel;                 // Kernel segment selector.
   u8int  always0;             // This must always be zero.
   u8int  flags;               // More flags. See documentation.
   u16int base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   u16int limit;
   u32int base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C" {
    extern void isr0 ();
    extern void isr1 ();
    extern void isr2 ();
    extern void isr3 ();
    extern void isr4 ();
    extern void isr5 ();
    extern void isr6 ();
    extern void isr7 ();
    extern void isr8 ();
    extern void isr9 ();
    extern void isr10 ();
    extern void isr11 ();
    extern void isr12 ();
    extern void isr13 ();
    extern void isr14 ();
    extern void isr15 ();
    extern void isr16 ();
    extern void isr17 ();
    extern void isr18 ();
    extern void isr19 ();
    extern void isr20 ();
    extern void isr21 ();
    extern void isr22 ();
    extern void isr23 ();
    extern void isr24 ();
    extern void isr25 ();
    extern void isr26 ();
    extern void isr27 ();
    extern void isr28 ();
    extern void isr29 ();
    extern void isr30 ();
    extern void isr31 (); 
}

extern void idt_flush(u32int);

static void idt_set_gate(u8int,u32int,u16int,u8int);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_descriptor_tables()
{
  init_gdt();
  init_idt();
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
} 

void set_gates() 
{
    idt_set_gate( 0, (u32int)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (u32int)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (u32int)isr2, 0x08, 0x8E);
    idt_set_gate( 3, (u32int)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (u32int)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (u32int)isr5, 0x08, 0x8E);
    idt_set_gate( 6, (u32int)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (u32int)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (u32int)isr8, 0x08, 0x8E);
    idt_set_gate( 9, (u32int)isr9 , 0x08, 0x8E);
    idt_set_gate( 10, (u32int)isr10 , 0x08, 0x8E);
    idt_set_gate( 11, (u32int)isr11, 0x08, 0x8E);
    idt_set_gate( 12, (u32int)isr12 , 0x08, 0x8E);
    idt_set_gate( 13, (u32int)isr13 , 0x08, 0x8E);
    idt_set_gate( 14, (u32int)isr14, 0x08, 0x8E);
    idt_set_gate( 15, (u32int)isr15 , 0x08, 0x8E);
    idt_set_gate( 16, (u32int)isr16 , 0x08, 0x8E);
    idt_set_gate( 17, (u32int)isr17, 0x08, 0x8E);
    idt_set_gate( 18, (u32int)isr18 , 0x08, 0x8E);
    idt_set_gate( 19, (u32int)isr19 , 0x08, 0x8E);
    idt_set_gate( 20, (u32int)isr20, 0x08, 0x8E);
    idt_set_gate( 21, (u32int)isr21 , 0x08, 0x8E);
    idt_set_gate( 22, (u32int)isr22 , 0x08, 0x8E);
    idt_set_gate( 23, (u32int)isr23, 0x08, 0x8E);
    idt_set_gate( 24, (u32int)isr24 , 0x08, 0x8E);
    idt_set_gate( 25, (u32int)isr25 , 0x08, 0x8E);
    idt_set_gate( 26, (u32int)isr26, 0x08, 0x8E);
    idt_set_gate( 27, (u32int)isr27 , 0x08, 0x8E);
    idt_set_gate( 28, (u32int)isr28 , 0x08, 0x8E);
    idt_set_gate( 29, (u32int)isr29, 0x08, 0x8E);
    idt_set_gate( 30, (u32int)isr30 , 0x08, 0x8E);
    idt_set_gate( 31, (u32int)isr31 , 0x08, 0x8E);
}

void memset(void *dest, int val, unsigned int len)
{
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

void init_idt()
{
   idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
   idt_ptr.base  = (u32int)&idt_entries;

   memset(&idt_entries, 0, sizeof(idt_entry_t)*256);
   
   set_gates();

   idt_flush((u32int)&idt_ptr);
}