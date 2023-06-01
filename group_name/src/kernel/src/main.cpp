#include <system.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

class OperatingSystem {
    int tick = 0;

public:
    OperatingSystem() {}

    void init() {
        print("Initializing UiA Operating System....");
    }

    
    void interrupt_handler_4(UiAOS::CPU::ISR::registers_t regs) {
        print("Called Interrupt Handler 4!");
    }

    void interrupt_handler_5(UiAOS::CPU::ISR::registers_t regs) {
        print("Called Interrupt Handler 5!");
        
    }

    void interrupt_handler_6(UiAOS::CPU::ISR::registers_t regs) {
        print("Called Interrupt Handler 6!");
    }

    void timer() {
        tick++;
        if(tick % 100 == 0){
        }
    }
};




void kernel_main()
{
    
    print("Hello, world");
    // print_int(56);

    auto os = OperatingSystem();
    os.init();


     UiAOS::CPU::ISR::register_interrupt_handler(4,[](UiAOS::CPU::ISR::registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_4(*regs);
    }, (void*)&os);

     UiAOS::CPU::ISR::register_interrupt_handler(5,[](UiAOS::CPU::ISR::registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_5(*regs);
    }, (void*)&os);

     UiAOS::CPU::ISR::register_interrupt_handler(6,[](UiAOS::CPU::ISR::registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_6(*regs);
    }, (void*)&os);

    asm volatile ("int $0x4");
    asm volatile ("int $0x5");
    asm volatile ("int $0x6");

    asm volatile("sti");
    
     UiAOS::CPU::PIT::init_timer(1, [](UiAOS::CPU::ISR::registers_t*regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->timer();
    }, &os);

    
    
     UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){
        auto* os = (OperatingSystem*)context;
    }, &os);

    
   


    while(1){}

}
