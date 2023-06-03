#ifndef PIT_H
#define PIT_H
#include <stdint.h>
#include <stdbool.h>
#include "common.h"



void init_timer();
void sleeping_busy(uint32_t sleep_tick);
void timer_phase(uint32_t frequency);
void sleeping_interrupts(uint32_t sleep_tick);





#endif