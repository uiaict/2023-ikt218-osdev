#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

class PIT{

public:
    static void init_timer(uint32_t freq,isr_t handler, void* context);

};


#endif //TIMER_H