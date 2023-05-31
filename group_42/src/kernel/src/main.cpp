
#include "test.h"
#include"keyboard/keyboard.h"
#include"memory/functions.h"
#include"PIT/pit.h"


extern uint32_t end;
class IJI_OS{
    int tick = 0;
    int tmp = 0;
    int color = 0x0B;
    volatile char *address = (volatile char*)0xB8000;
    volatile char *next_address = (volatile char*)0xB8000 + 160;
    int line = 0;
    public:
    

void write_string_2(const char *string){
 
    if(tmp>3500){
        clearScreen();
        line = 0;
    }
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }
}

void next_line(){
    address = next_address;
    next_address = next_address + 160;

}

void write_char_2( char c){
    tmp = tmp+1;
    *address++ = c;
    *address++ = color;
    *address = 0x0B;
}
void write_integer(char* string, uint32_t a){
    if(tmp>3500){
        clearScreen();
        line = 0;
    }
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }

    char reverseDigits[64];
    int counter = 0;
    while (a>0){
        char nextDigit = a%10+'0';
        reverseDigits[counter] = nextDigit;
        a = a/10;
        counter = counter + 1;
    }
    counter = counter-1;
    while (counter>=0){
           *address++ = reverseDigits[counter];
            *address++ = color;
            counter = counter-1;
        }
    }
 
void write_hexadecimal(char* string, uint32_t a){
    if(tmp>3500){
        clearScreen();
        line = 0;
    }
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }
    char reverseDigits[64];
    char nextDigit;
    int counter = 0;
    while (a>0){
        int leftovers = a%16;
        if (leftovers < 10){
            nextDigit = leftovers + '0';
        }
        else{
            nextDigit = leftovers - 10 + 'a';
        }
        reverseDigits[counter] = nextDigit;
        a = a/16;
        counter = counter + 1;
    }
    counter = counter-1;
    while (counter>=0){
           *address++ = reverseDigits[counter];
            *address++ = color;
            counter = counter-1;
        }
 
}

void interrupt_handler_3(UiAOS::CPU::ISR::registers_t regs){
    write_string_2("interrupt   3");
    next_line();
}
void interrupt_handler_2(UiAOS::CPU::ISR::registers_t regs){
    write_string_2("interrupt  2");
    next_line();
}
void interrupt_handler_1(UiAOS::CPU::ISR::registers_t regs){
    write_string_2("interrupt 1");
    next_line();
}

void init(){
        clearScreen();
        write_string_2( "Hello World!");
        next_line();

    }

};
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
write_memorylayout();
asm volatile("sti");
 UiAOS::IO::Keyboard::hook_keyboard([](uint8_t scancode, void* context){
    auto* os = (IJI_OS*)context;
    //os->write_string_2("Keyboard Event: ");
    //os->next_line();
    os->write_char_2(UiAOS::IO::Keyboard::scancode_to_ascii(scancode));
    //os->write_string_2("hello");
    //os->next_line();
    },&os); 
//sleep_interrupt((uint32_t) 10);
//asm volatile ("int $0x01");
start_sleep_busy((uint32_t) 10000);

//asm volatile ("int $0x01");
//os.write_string_2("hello dwadwajifohesifuhwiuegfydguywuda");


 
}