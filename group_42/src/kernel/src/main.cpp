#include "test.h"
#include"keyboard/keyboard.h"
#include"memory/functions.h"
#include"PIT/pit.h"
#include "OS_class/OS_class.h"


extern "C"{
    void kernel_main();
}



void kernel_main()
{   
    
   init_pag(); // Initialize paging for memory management
   auto os = IJI_OS(); 
   os.init(); // clear the screen and write "Hello World!"
   init_pit(); // starts the programmable interval timer
 

 // these functions register the interrupt handlers in the interrupt descriptor table
 UiAOS::CPU::ISR::register_interrupt_handler(3,[](UiAOS::CPU::ISR::registers_t* regs, void* context){ 
    auto* os = (IJI_OS*)context;
    os->interrupt_handler_3(*regs);
 }, (void*)&os);
 UiAOS::CPU::ISR::register_interrupt_handler(2,[](UiAOS::CPU::ISR::registers_t* regs, void* context){
    auto* os = (IJI_OS*)context;
    os->interrupt_handler_2(*regs);
 }, (void*)&os);
 UiAOS::CPU::ISR::register_interrupt_handler(1,[](UiAOS::CPU::ISR::registers_t* regs, void* context){
    auto* os = (IJI_OS*)context;
    os->interrupt_handler_1(*regs);
 }, (void*)&os);

asm volatile("sti"); // This enables interrupts, allowing pit and the keyboard function
 UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){ // This function is triggered when we push a button on the keyboard
    auto* os = (IJI_OS*)context;
    os->write_char(UiAOS::IO::Keyboard::scancode_to_ascii(scancode)); // This writes the character from the keyboard
    },&os); 

// We trigger our interrupts to show that our interrupt handlers work
asm volatile ("int $0x03");
asm volatile ("int $0x02");
asm volatile ("int $0x01");
start_sleep_busy((uint32_t) 10000); // this line demonstrates functionality of sleep call


// below we assign some memory to show that our memory manager works
 char* a = new char[10]();
 a[9]='5';
void* mem1 = malloc(12);
 void* mem2 = malloc(1200);
 void* mem3 = malloc(12);
os.print_memory_layout();
start_sleep_busy((uint32_t) 10000);
 delete mem2;
 void* mem4 = malloc(12);
 int c = 2;

os.print_memory_layout(); //Display functioning paging
// Sleep with enabled interrupts to show that it works
 

while (1)
{
   sleep_interrupt(10000); 
}

}