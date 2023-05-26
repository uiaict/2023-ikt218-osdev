


// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"

    void kernel_main();
}

void kernel_main()
{
    clear_terminal();

    print_logo();


    char str[] = "Hello, Wolrd!";
    printf("%s\n", str);    
    
}
