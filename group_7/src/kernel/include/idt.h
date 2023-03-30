#ifndef IDT_H
#define IDT_H
/*
This header file contains the definitions of the functions that create 
an interupt descriptor table (idt) in our os. The table defines
interupt numbers and points to interupt handling functions that deals
with the issue or reason for the interupt.

The documentation of this file is done with help of the IDt article at osDev
https://wiki.osdev.org/Interrupt_Descriptor_Table

*/
#include <stdint.h>

#define IDT_ENTRIES 256 // this os may have a total of 256 different interupts.

/**
 * @brief Defines the structure of an idt entry.
 * 
 */
struct idt_entry_t {
  /// @brief offset bits 0..15 of the base address.
  uint16_t base_low;
  /// @brief a code segment selector. Point to a field of executable code.
  uint16_t selector;
  /// @brief A reserved field that must be 0x00
  uint8_t zero;
  /// @brief  the gate type, dpl (CPU privelige level) and p (present bit) fields
  uint8_t flags;
  /// @brief offset bits 16...31 of the base address..
  uint16_t base_high;
} __attribute__((packed)); // reduces the size of the struct in memory.

/**
 * @brief A pointer to the idt table.
 * The base is the lowest address, and the start of the table
 * The limit is the highest address of the idt.
 */
struct idt_ptr_t {
  /// the highest accessable address in the idt. I.e. the last idt entry.
  uint16_t limit; 
  /// the first accessable address in the idt.
  uint32_t base; 
} __attribute__((packed)); // reduces the size of the struct in memory.

/**
 * @brief Creates and loads the idt table and its interupts.
 * First, it creates the idt_ptr, then fills the table 
 * with idt entries, inserts the data into the 
 * interupt handler (see interupts.h), and then loads
 * the idt using asm.
 */
void init_idt();


/// @brief The idt table of 256 entries.
static idt_entry_t idt[IDT_ENTRIES];
/// @brief pointer to the idt table and variable.
static idt_ptr_t idt_ptr;

#endif