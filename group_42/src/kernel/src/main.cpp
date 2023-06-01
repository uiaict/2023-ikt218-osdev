#include "test.h"
#include"keyboard/keyboard.h"
#include"memory/functions.h"
#include"PIT/pit.h"

#include "OS_class/OS_class.h"
extern uint32_t end;

extern "C"{
    void kernel_main();
}



void kernel_main()
{   
    

    
    init_pag();
   auto os = IJI_OS();
   os.init();
   init_init_pit();
 
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



/* 
asm volatile ("int $0x03");
asm volatile ("int $0x02");
asm volatile ("int $0x01");
 */

 char* a = new char[10]();
 a[9]='5';

void* mem1 = malloc(12);
 void* mem2 = malloc(12);
 void* mem3 = malloc(12);
 free(mem3);
 void* mem4 = malloc(12);
 int c = 2;
os.write_hexadecimal("Check out this, a memory address!!!: 0x", 5042);

asm volatile("sti");
 UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){
    auto* os = (IJI_OS*)context;
    //os->write_string_2("Keyboard Event: ");
    //os->next_line();
    os->write_char(UiAOS::IO::Keyboard::scancode_to_ascii(scancode));
    //os->write_string_2("hello");
    //os->next_line();
    },&os); 
//sleep_interrupt((uint32_t) 10);
//asm volatile ("int $0x01");
start_sleep_busy((uint32_t) 10000);

//asm volatile ("int $0x01");
//os.write_string_2("hello dwadwajifohesifuhwiuegfydguywuda");


 
}