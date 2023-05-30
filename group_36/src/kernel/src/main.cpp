// define entry point
extern "C"{
    void kernel_main();
}


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../cpu/i386/gdt.h"
#include "../cpu/i386/idt.h"
// #include "../cpu/i386/isr.h"
#include <stdlib/c/libc.h>
#include "../drivers/_include/driver.h"
#include <../cpu/include/cpu.h>
#include <../cpu/i386/timer/timer.h>
#include "../memory/paging.h"
#include "boot.h"
#include "print.h"
// #include "../memory/kmalloc.h"
extern uint32_t end;


 
#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif





class OperatingSystem {
    int tick = 0;
    int seconds = 0;

public:
    bool keyboard_input_enabled = true;
    
    OperatingSystem(vga_color color) {

    }

    void init() {

        // printf("Initializing Operating System....\n");
    }

    void debug_print(char *str) {
        printf(str);
    }

    void interrupt_handler_1(registers_t regs) {
        printf("Called Interrupt Handler 1!\n");
    }

    void interrupt_handler_3(registers_t regs) {
        printf("Called Interrupt Handler 3!\n");
    }

    void interrupt_handler_4(registers_t regs) {
        printf("Called Interrupt Handler 4!\n");
    }

    void timer() {
        tick++;
        if (tick % 100 == 0) {
            seconds++;
            // printf("(Every Second) Tick: ");
            // print_uint8(tick);
            // printf("\n");
        }
    }

    int get_tick(){
        return tick;
    }

    void print_time() {
        printf("[Time: ");
        print_uint8(seconds);
        printf("]$ ");
    }

    void sleep_busy(int seconds_) {
        // asm volatile("cli");
        keyboard_input_enabled = false;
        int current_tick = get_tick();
        int ticks_to_wait = seconds_*100;
        int end_ticks = current_tick + ticks_to_wait;
        while(current_tick < end_ticks){
            current_tick = get_tick();
        }
        // asm volatile("sti");
        keyboard_input_enabled = true;
    }
    

    void sleep_interrupt(int seconds_) {
        int current_tick = get_tick();
        int ticks_to_wait = seconds_*100;
        int end_ticks = current_tick + ticks_to_wait;
        while(current_tick < end_ticks){
            asm volatile("sti");
            asm volatile("hlt");
            current_tick = get_tick();
        }
    }
};

void* operator new[](size_t size) {
    return reinterpret_cast<void*>(kmalloc(size));
}

void kernel_main(void) 
{

	/* Initialize terminal interface */
	terminal_initialize();

    printf("Starting OS...\n");

    // initialize paging
    printf("Initializing paging...\n");
    init_paging();

 
	// Initialize GDT
	printf("\nInitializing GDT...\n");
    init_gdt();
    
    // initialize IDT
    printf("Initializing IDT...\n");
    init_idt();


    // initialize ISRs ##########################################
    printf("Initializing ISRs...");
    init_isr();

	// Create operating system object
    auto os = OperatingSystem(VGA_COLOR_RED);
    os.init();
    
    // Create interrupt handler for ISR1
    register_interrupt_handler(1,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_1(*regs);
    }, (void*)&os);

    // Create interrupt handler for ISR3
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_3(*regs);
    }, (void*)&os);
    
    // Create interrupt handler for ISR4
    register_interrupt_handler(4,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_4(*regs);
    }, (void*)&os);

    // Create a timer on IRQ0 - System Timer
    PIT::init_timer(1, [](registers_t*regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->timer();
    }, &os);

	printf("Initialized!\n");
	printf("Hello World!! \n");
    
    // Fire interrupts
    asm volatile ("int $0x1");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    // Enable interrutps
    asm volatile("sti");



    int phys = kmalloc_ap(sizeof(int), 0x000);
    printf("0x");
    print_int(phys);
    printf("\nmemory address^\n");

    os.print_time();

    // Hook Keyboard
   Keyboard::hook_keyboard([](uint8_t scancode, void* context){
        auto* os = (OperatingSystem*)context;
        
        if (!os->keyboard_input_enabled) {return;}

        // for assignment:
        printf("Keyboard interrupt triggered: ");

        char ascii[2] = {Keyboard::scancode_to_ascii(scancode), '\0'};
        printf(ascii);
        printf("\n");

        if(ascii[0] == 10){ os->print_time(); } // print time if newline
    }, &os);

    int counter = 0;
    printf("Sleeping with busy-waiting for 5 seconds (HIGH CPU)...\n");
    // print_int(counter);
    // printf("\n");
    os.sleep_busy(5);
    printf("Slept using busy-waiting.\n");
    // print_int(counter++);
    // printf("\n");
    printf("Sleeping with interrupts for 5 seconds (LOW CPU)...\n");
    // print_int(counter);
    // printf("\n");
    os.sleep_interrupt(5);
    printf("Slept using interrupts.\n");
    // print_int(counter++);
    // printf("\n");


    while(true){}
    // while(1){}
}