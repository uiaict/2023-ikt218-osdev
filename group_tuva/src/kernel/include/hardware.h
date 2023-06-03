#ifndef HARDWARE_H
#define HARDWARE_H

#include "common.h"


#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)


#endif //HARDWARE_H