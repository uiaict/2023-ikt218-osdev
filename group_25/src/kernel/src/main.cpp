#include "gdt.h"
#include "terminal.h"
#include "system.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main(){

// Initialize global descriptor table
init_gdt();

// Initialize terminal
terminal_initialize();

// Print welcome screen
// Kinda scuffed because I couldn't find a nice way to space the text out
terminal_write("                _____ __    _ __      ____  _____                                              / ___// /_  (_) /_    / __ \\/ ___/                                              \\__ \\/ __ \\/ / __/   / / / /\\__ \\                                              ___/ / / / / / /_    / /_/ /___/ /                                             /____/_/ /_/_/\\__/____\\____//____/                                                              /_____/                                                      ____       __           __          __    _ __                                 /  _/      / /_  _______/ /_   _____/ /_  (_) /_                                / /   __  / / / / / ___/ __/  / ___/ __ \\/ / __/                              _/ /   / /_/ / /_/ (__  ) /_   (__  ) / / / / /_                               /___/   \\____/\\__,_/____/\\__/  /____/_/ /_/_/\\__/                                              _                                 __                          __  ______  __  _( )________     ____  ____ _____  / /______                   / / / / __ \\/ / / /// ___/ _ \\   / __ \\/ __ `/ __ \\/ __/ ___/                  / /_/ / /_/ / /_/ / / /  /  __/  / /_/ / /_/ / / / / /_(__  )                   \\__, /\\____/\\__,_/ /_/   \\___/  / .___/\\__,_/_/ /_/\\__/____/                   /____/                          /_/\n\n",
1317);

terminal_write("Hello World!\n", 14);

}