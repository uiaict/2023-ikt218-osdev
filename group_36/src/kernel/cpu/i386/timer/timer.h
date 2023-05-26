#include <stdint.h>

namespace UiAOS::CPU{
    class PIT{
    public:
        static void init_timer(uint32_t freq, UiAOS::CPU::ISR::isr_t handler, void* context);
    };
}