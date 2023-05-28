#include "functions.h"
#include "system.h"
#include "memory.h"
#include <stdlib.h>




void* operator new(std::size_t size){
    return malloc(size);
}
void* operator new[](std::size_t size){
    return malloc(size);
} 
