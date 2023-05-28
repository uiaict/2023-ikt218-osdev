#include "functions.h"

#include <stdlib.h>




void* operator new(std::size_t size){
    return malloc(size);
}
void* operator new[](std::size_t size){
    return malloc(size);
}