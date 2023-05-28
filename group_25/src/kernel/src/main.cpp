#include "terminal.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    #include "system.h"
    void kernel_main();
}

void kernel_main(){

    terminal_clear();
    // Print welcome screen
    terminal_write("                _____ __    _ __      ____  _____\n");
    terminal_write("               / ___// /_  (_) /_    / __ \\/ ___/\n");
    terminal_write("               \\__ \\/ __ \\/ / __/   / / / /\\__ \\\n");
    terminal_write("              ___/ / / / / / /_    / /_/ /___/ /\n");
    terminal_write("             /____/_/ /_/_/\\__/____\\____//____/\n");
    terminal_write("         ____     _          /_____/       __    _ __\n");
    terminal_write("        /  _/    (_)_  _______/ /_   _____/ /_  (_) /_\n");
    terminal_write("        / /     / / / / / ___/ __/  / ___/ __ \\/ / __/\n");
    terminal_write("      _/ /     / / /_/ (__  ) /_   (__  ) / / / / /_\n");
    terminal_write("     /___/  __/ /\\__,_/____/\\__/  /____/_/ /_/_/\\__/ __\n");
    terminal_write("   __  ____/___/_  __________     ____  ____ _____  / /______\n");
    terminal_write("  / / / / __ \\/ / / / ___/ _ \\   / __ \\/ __ `/ __ \\/ __/ ___/\n");
    terminal_write(" / /_/ / /_/ / /_/ / /  /  __/  / /_/ / /_/ / / / / /_(__  )\n");
    terminal_write(" \\__, /\\____/\\__,_/_/   \\___/  / .___/\\__,_/_/ /_/\\__/____/\n");
    terminal_write("/____/                        /_/\n");
    
    terminal_write("Hello World!\n");

    // Print a message and enter an infinite loop to wait for interrupts
    terminal_write("Waiting...\n");
    while(1){};
    terminal_write("Done!...\n");

}