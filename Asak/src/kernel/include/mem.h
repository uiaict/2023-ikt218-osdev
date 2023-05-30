#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

void mm_init(uint32_t kernel_end);
void mm_print_out();


//Overload 1
void* operator new(size_t size);
void operator delete(void* ptr);

// Overload 2
void operator delete[](void* ptr);
void* operator new[](size_t size);

void free(void *mem);
char* malloc(size_t size);
void* memset(void* bufptr, int value, size_t size);
