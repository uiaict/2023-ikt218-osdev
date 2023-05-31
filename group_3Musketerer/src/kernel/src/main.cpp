extern "C" {

    #include "print.h"
    #include "system.h"
}


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}


void kernel_main()
{
    /*Vi trenger ikke ha init_gdt i main siden vi kaller den i boot.asm, er ingen synnlig forskjell
    Tror eneste feilen pt er at det er undefined reference på den, vet ikke helt hvorfor for å være helt ørlig
    den burde ligge i system.h og ikke at vi inkluderer gdt.h her, tror det er samme problem som jeg 
    hadde med write_terminal
    */ 
    //init_gdt();
    print_clear();
    print_str("Hello World");
    print_str("\n");
    print_str("NYYYY Linje");
}
