#include <stdint.h>
#include <stdlib.h>
//#include "memory.h"


void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void init_pag();

void write_memorylayout();

void start_sleep_busy(uint32_t milliseconds);