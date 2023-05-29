#include <stdint.h>
#include <stddef.h>

//Overload 1
void* operator new(size_t size);
void operator delete(void* ptr);

// Overload 2
void operator delete[](void* ptr);
void* operator new[](size_t size);

