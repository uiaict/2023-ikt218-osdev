#include "libc/system.h"
#include <stdarg.h>
#include <stdio.h>

// less risky when the stack is blown out
static char buffer[4096];

#define frp(N, ra)                                 \
  (__builtin_frame_address(N) != nullptr) &&       \
  (ra = __builtin_return_address(N)) != nullptr && ra != (void*)-1

static void print_trace(const int N, const void* ra)
{
  printf(buffer, sizeof(buffer),
          "[%d] %p\n",
          N, ra);
  printf(buffer);
}

extern "C"
void print_backtrace()
{
  printf("\nBacktrace:\n");
  void* ra;
  if (frp(0, ra)) {
    print_trace(0, ra);
    if (frp(1, ra)) {
      print_trace(1, ra);
      if (frp(2, ra)) {
        print_trace(2, ra);
      }
    }
  }
}

__attribute__((noreturn))
void panic(const char* reason)
{
	printf("\n\n!!! PANIC !!!\n%s\n", reason);

	print_backtrace();

	// the end
	printf("\nKernel halting...\n");
	while (1) asm("cli; hlt");
	__builtin_unreachable();
}


void abort()
{
	panic("Abort called");
}
