// copied from given github reposetory

#ifndef IJI_OS_GDT_H
#define IJI_OS_GDT_H
#include <stdint.h>

namespace IJI_OS::GDT
{
  
  typedef struct
  {
    uint16_t limit_low;     // limits the size 
    uint16_t base_low;    // memory address
    uint8_t base_middle; // memory address
    uint8_t access;     // assign the acess level of the segment
    uint8_t granularity; // scale of the limit
    uint8_t base_high; // memory address
  } gdt_entry_t;


  typedef struct __attribute__((packed))
  {
    uint16_t limit; // limits the size of the object
    uint32_t base;  // memmory address of the size
  } gdt_ptr_t;


  void init_gdt();  // function that inizilases the GDT
  void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran); // sets a segment of the GDT

}

#endif