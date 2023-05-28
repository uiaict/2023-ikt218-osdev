#include "functions.h"

extern "C"{
   #include"memory.h"
     void init_kernel();
    
}

 extern uint32_t end;
 void init_kernel(){
   
    init_kernel_memory(&end);
    int a = 2;
 }
void* operator new(std::size_t size){
    return malloc(size);
}
void* operator new[](std::size_t size){
    return malloc(size);
} 
