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

    void timer() {
        tick++;
        if(tick % 100 == 0){
            //print("(Every Second) Tick: ");
            //print_int(tick);
            //print(" ");
        }
    }
};






void my_keyboard_callback(uint8_t scancode, void* ctx) {
    print("Inside callback");
    // Add your code to handle the keyboard callback here
}



void kernel_main()
{
    
    print("Hello, world");
    print_int(5);

    auto os = OperatingSystem();
    os.init();

    asm volatile("sti");

     UiAOS::CPU::PIT::init_timer(1, [](UiAOS::CPU::ISR::registers_t*regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->timer();
    }, &os);

    // Hook the keyboard
    UiAOS::IO::Keyboard::hook_keyboard(my_keyboard_callback, nullptr);
    
     UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){
        auto* os = (OperatingSystem*)context;
        //print("Keyboard Event: ");
        print_int(UiAOS::IO::Keyboard::scancode_to_ascii(scancode));
        //print(" (");
        //print_int(scancode);
        //print(")");
    }, &os);

    
   


    while(1){}

}
