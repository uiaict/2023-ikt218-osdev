//
// Created by per on 12/31/22.
//

#ifndef UIAOS_HARDWARE_H
#define UIAOS_HARDWARE_H

#include "hardware_port.h"


#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)


#endif //UIAOS_HARDWARE_H
