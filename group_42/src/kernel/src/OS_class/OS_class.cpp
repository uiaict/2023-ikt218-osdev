#include "OS_class.h"
#include <stdint.h>
#include <stdlib.h>

#include"../keyboard/keyboard.h"
#include"../memory/functions.h"
//#include "../memory/memory.h"
#include"../PIT/pit.h"
#define VGA_ADDRESS 0xB8000 // The starting address of the VGA buffer 
#define BUFSIZE 4000       // the size of the memory area
extern "C"{ // functions imported from c
    uint32_t get_heap_end();
    uint32_t get_pheap_end();
    uint32_t get_last_alloc();
    uint32_t get_heap_begin();
    uint32_t get_pheap_begin();
     uint32_t get_memory_used();

}


void IJI_OS::write_string(const char *string){// function to write a string
 
    while( *string != 0 )// while string is not empty
    {
        *address++ = *string++; // adress = first letter of string  and increment bouth the string and the adress
        *address++ = color;     //      sett adress to collor and increment adress              
    }
}

void IJI_OS::next_line(){ // function that moves the writing adress to the first letter of the first line
    address = next_address;
    next_address = next_address + 160;

}

void IJI_OS::write_char( char c){// function that writes a char
    tmp = tmp+1;
    *address++ = c;
    *address++ = color;
    *address = 0x0B;
}
void IJI_OS::write_integer(char* string, uint32_t a){// function to write intereger 
 
   
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
 
void IJI_OS::write_hexadecimal(char* string, uint32_t a){// function to write hexadecimal
 
   
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
            nextDigit = leftovers - 10 + 'A';
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
void IJI_OS::clearScreen()// function to clear the screen and move the adress 
{
     uint8_t *vga = (uint8_t*) VGA_ADDRESS;
    for (int i = 0; i < BUFSIZE; i++)
    {
        vga[i] = 0;
    } 
    address = (volatile char*)0xB8000;
    next_address = (volatile char*)0xB8000 + 160;
}

void IJI_OS::print_memory_layout(){// function to print the memory layout
    clearScreen();
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
// below are the interupt handlers that has the task to write on the screen what interupt was triggered. 
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

void IJI_OS::init(){// function that clears the screan and writes hello world
        clearScreen();
        write_string( "Hello World!");
        next_line();

    }
