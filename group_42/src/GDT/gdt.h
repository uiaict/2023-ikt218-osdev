#ifndef IJI_OS_GDT_H
#define IJI_OS_GDT_H
#include <stdint.h>

namespace IJI_OS::GDT
{
  // Structure to hole one global descriptor table entry
  typedef struct
  {
    uint16_t limit_low;  // The lower 16 bits of the limit.
    uint16_t base_low;   // The lower 16 bits of the base.
    uint8_t base_middle; // The next 8 bits of the base.
    uint8_t access;      // Access flags, determine what ring this segment can be used in.
    uint8_t granularity;
    uint8_t base_high; // The last 8 bits of the base.
  } gdt_entry_t;

  // Struct to hold the base pointer and limit pointer of the global descriptor table
  typedef struct __attribute__((packed))
  {
    uint16_t limit; // The upper 16 bits of all selector limits.
    uint32_t base;  // The address of the first gdt_entry_t struct.
  } gdt_ptr_t;


  void init_gdt();
  void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

}

#endif