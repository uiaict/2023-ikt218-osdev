#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif
void outb(uint16_t port, uint8_t value);
#ifdef __cplusplus
}
#endif


uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);