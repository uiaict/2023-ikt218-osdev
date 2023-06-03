#include <stdint.h>

class PIT{
public:
    static void init_timer(uint32_t freq, isr_t handler, void* context);
};