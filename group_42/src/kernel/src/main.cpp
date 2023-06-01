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
    
   init_pag(); // inzisilize paging for memory management
   auto os = IJI_OS(); 
   os.init(); // clear the screen and write hello
   init_pit(); // starts the Programable intervall timer
 

 // these functions connect the interupts handlers to the interupt descriptor table
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

asm volatile("sti"); // this enables interupts allowing pit and the keyboard function below to 
 UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){ // this function is triggered when we push a button on the keyboard
    auto* os = (IJI_OS*)context;
    os->write_char(UiAOS::IO::Keyboard::scancode_to_ascii(scancode)); // this writes the character from the keyboard
    },&os); 

// this is to show that our interupt handlers work
asm volatile ("int $0x03");
asm volatile ("int $0x02");
asm volatile ("int $0x01");
start_sleep_busy((uint32_t) 10000); // this gives you time to see that booth our timer and our inerupt handler works


// below we assign some memory to show that our memory manager works
 char* a = new char[10]();
 a[9]='5';
void* mem1 = malloc(12);
 void* mem2 = malloc(1200);
 void* mem3 = malloc(12);
os.print_memory_layout();
start_sleep_busy((uint32_t) 10000); // time to see the memory before we free som to show that it works
 free(mem2);
 void* mem4 = malloc(12);
 int c = 2;

os.print_memory_layout();
sleep_interrupt(10000); // again sleep to show that is works




 
}