#ifndef IJI_OS_GDT_H
#define IJI_OS_GDT_H
#include <stdint.h>

namespace IJI_OS::GDT
{
  
  typedef struct
  {
    uint16_t limit_low; 
    uint16_t base_low;   
    uint8_t base_middle; 
    uint8_t access;     
    uint8_t granularity;
    uint8_t base_high; 
  } gdt_entry_t;


  typedef struct __attribute__((packed))
  {
    uint16_t limit;
    uint32_t base;  
  } gdt_ptr_t;


  void init_gdt();
  void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

}

#endif