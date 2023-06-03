#include "common.h"

void output_to_port(uint16_t port, uint8_t value)
{
    __asm__ __volatile__("out %1, %0" : : "dN" (port), "a" (value));
}

uint8_t input_from_port(uint16_t port)
{
   uint8_t ret;
   __asm__ __volatile__("in %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}
