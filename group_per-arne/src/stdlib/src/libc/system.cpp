#include "libc/system.h"

extern "C"{
    void __stack_chk_fail_local();
    void __stack_chk_fail();
    void _exit(int status);
}

    __attribute__((noreturn)) void panic(const char*);
    void* _impure_ptr = NULL;


    void __stack_chk_fail_local()
    {
        panic("Stack protector: Canary modified");
        __builtin_unreachable();
    }
    __attribute__((used))
    void __stack_chk_fail()
    {
        panic("Stack protector: Canary modified");
        __builtin_unreachable();
    }

    void _exit(int status)
    {
        char buffer[64] = {};
        printf(buffer, sizeof(buffer), "Exit called with status %d\n", status);
        panic(buffer);
        __builtin_unreachable();
    }

