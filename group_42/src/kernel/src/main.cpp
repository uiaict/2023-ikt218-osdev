
//#include "system.h"
#include "test.h"
#include "../../GDT/isr.h"
class IJI_OS{
    int tick = 0;
    int color = 0x0B;
    //(uint16_t*) VGA = ;
    public:
    void init(){
        clearScreen();
        write_string(color, "Hello World!");

    }


void interrupt_handler_3(UiAOS::CPU::ISR::registers_t regs){
    write_string(color,"interrupt   3");

}
void interrupt_handler_2(UiAOS::CPU::ISR::registers_t regs){
    write_string(color,"interrupt  2");

}
void interrupt_handler_1(UiAOS::CPU::ISR::registers_t regs){
    write_string(color,"interrupt 1");

}


};
extern "C"{
    void kernel_main();
}

void kernel_main()
{
   auto os = IJI_OS();
   os.init();
   /* 
  UiAOS::CPU::ISR::register_interrupt_handler(3,[](UiAOS::CPU::ISR::registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_3(*regs);
    }, (void*)&os);
 */
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

asm volatile ("int $0x03");
asm volatile ("int $0x02");
asm volatile ("int $0x01");

}
