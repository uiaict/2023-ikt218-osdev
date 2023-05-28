#include <system.h>
#include "screen.h"
#include "keyboard.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void my_keyboard_callback(uint8_t scancode, void* ctx) {
    print("Inside callback");
    // Add your code to handle the keyboard callback here
}

void kernel_main()
{
    print("Hello, world");
    print_int(5);

    // Hook the keyboard
    UiAOS::IO::Keyboard::hook_keyboard(my_keyboard_callback, nullptr);

    asm volatile ("int $0x6");
    asm volatile ("int $0x8");

    
}
