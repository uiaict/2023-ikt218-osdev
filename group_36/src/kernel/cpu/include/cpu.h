//
// Created by per on 1/1/23.
//

#ifndef UIAOS_CPU_H
#define UIAOS_CPU_H

#if (i386 == i386)
#include "../i386/isr.h" // TODO
#include "../i386/hardware.h"
// #include "../i386/timer/timer.h"
#else
    // #error "Selected ARCH target is not supported for the CPU "
#endif
#endif //UIAOS_CPU_H
