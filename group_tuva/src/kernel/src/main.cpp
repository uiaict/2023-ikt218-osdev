#include "system.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "keyboard.h"
#include "hardware.h"
#include "timer.h"
// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
    //void init_descriptor_tables();
}
enum vga_color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};
class OperatingSystem {
    int tick = 0;

public:
    OperatingSystem(vga_color color) {
    }

    void init() {

        printf("Initializing UiA Operating System....");
        //print_new_line();
    }

    void debug_print(char *str) {
        printf(str);
        //print_new_line();
    }

    void interrupt_handler_3(registers_t regs) {
        printf("Called Interrupt Handler 3!");
        //print_new_line();
    }

    void interrupt_handler_4(registers_t regs) {
        printf("Called Interrupt Handler 4!");
        //print_new_line();
    }

    void timer() {
        tick++;
        if (tick % 100 == 0) {
            printf("(Every Second) Tick: ");
            //print_int(tick);
            //print_new_line();
        }

    }
};

// Main entry point for kernel
void kernel_main()
{
    auto os = OperatingSystem(WHITE);
    os.init();

    //printf("Hello");

    // Initializes the descriptor tables, and prints to indicate
    // that the GDT has been successfully initialized
    init_descriptor_tables();
    //printf("gdt initialized");
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_3(*regs);
    }, (void*)&os);

    // Create some interrupt handler for 4
    register_interrupt_handler(4,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_4(*regs);
    }, (void*)&os);


    // Fire interrupts! Should trigger callback above
    //asm volatile ("int $0x3");
    //asm volatile ("int $0x4");

    asm volatile("sti");
    PIT::init_timer(1, [](registers_t*regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->timer();
    }, &os);

    Keyboard::hook_keyboard([](uint8_t scancode, void* context){
        auto* os = (OperatingSystem*)context;
        printf("Keyboard Event: ");
        /*print_char(scancode_to_ascii(scancode));
        printf(" (");
        print_int(scancode);
        printf(")");
        print_new_line();*/
    }, &os);

    while (1)
    {}
    
}



