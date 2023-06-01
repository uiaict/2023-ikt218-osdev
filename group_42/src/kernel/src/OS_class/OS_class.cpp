#include "OS_class.h"
#include <stdint.h>
#include <stdlib.h>

#include"../keyboard/keyboard.h"
#include"../memory/functions.h"
//#include "../memory/memory.h"
#include"../PIT/pit.h"

extern "C"{
    uint32_t get_heap_end();

    uint32_t get_pheap_end();
    uint32_t get_last_alloc();
    uint32_t get_heap_begin();
    uint32_t get_pheap_begin();
     uint32_t get_memory_used();
//    uint32_t get_pheap_begin();
}


void IJI_OS::write_string(const char *string){
 
    
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }
}

void IJI_OS::next_line(){
    address = next_address;
    next_address = next_address + 160;

}

void IJI_OS::write_char( char c){
    tmp = tmp+1;
    *address++ = c;
    *address++ = color;
    *address = 0x0B;
}
void IJI_OS::write_integer(char* string, uint32_t a){
 
   
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
 
void IJI_OS::write_hexadecimal(char* string, uint32_t a){
 
   
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

void IJI_OS::print_memory_layout(){
    uint32_t last_alloc = get_last_alloc();
    uint32_t heap_end = get_heap_end();
    uint32_t heap_begin = get_heap_begin();
    uint32_t pheap_begin = get_pheap_begin();
    uint32_t pheap_end = get_pheap_end();
    uint32_t memory_used = get_memory_used();

    write_integer("Memory used: ",memory_used);
    write_string(" bytes");
    next_line();
    write_integer("Memory free: ", heap_end-heap_begin-memory_used);
    write_string(" bytes");
    next_line();
    write_integer("Heap size: ", heap_end-heap_begin);
    write_string(" bytes");
    next_line();
    write_hexadecimal("Heap start: 0x",heap_begin);
    next_line();
    write_hexadecimal("Heap end: 0x", heap_end);
    next_line();
    write_hexadecimal("PHeap start: 0x", pheap_begin);
    next_line();
    write_hexadecimal("PHeap end: 0x", pheap_end);
    
}

void IJI_OS::interrupt_handler_3(UiAOS::CPU::ISR::registers_t regs){
    write_string("interrupt   3");
    next_line();
}
void IJI_OS::interrupt_handler_2(UiAOS::CPU::ISR::registers_t regs){
    write_string("interrupt  2");
    next_line();
}
void IJI_OS::interrupt_handler_1(UiAOS::CPU::ISR::registers_t regs){
    write_string("interrupt 1");
    next_line();
}

void IJI_OS::init(){
        
        write_string( "Hello World!");
        next_line();

    }