
#include "system.h"
#include "../screen/screen.h"
#include "../src/CPU/table.h"

/*#include <cstdlib>*/
/*extern uint32_t end; // This is defined in linker.ld*/

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
 
}

void kernel_main() {
    /* Initialize terminal interface */
	screenInitialize();
	screenWriteString("Hello World!");




    // Initialize Global Descriptor Table (GDT)
    init_gdt();


}

