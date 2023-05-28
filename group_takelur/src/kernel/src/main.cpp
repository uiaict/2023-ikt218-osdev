// Define entry point in asm to prevent C++ mangling
extern "C" {
    #include "common.h"
    #include "system.h"
    #include "monitor.h"
    #include "gdt.h"
    void kernel_main();
}

void kernel_main() {
    // Initialize the GDT
    init_descriptor_tables();

    clear_monitor();
    monitor_write("Welcome to OS version 0.0.001!\n", 0, 15);
    monitor_write("This should be on a new line\n\n", 0, 15);
    monitor_write("Does tabs work? : 1\t2\t3\t4\t5\n", 0, 15);
    monitor_write("Backspaces? : 1 \b2\b3 \b4\b5\n", 0, 15);
    monitor_write("BG colors? : ", 0, 15);
    monitor_write("RED ", 4, 15);
    monitor_write("GREEN ", 2, 15);
    monitor_write("BLUE \n", 1, 15);
    monitor_write("FG colors? : ", 0, 15);
    monitor_write("RED ", 0, 4);
    monitor_write("GREEN ", 0, 2);
    monitor_write("BLUE \n", 0, 1);
    monitor_write("\nWill now test scrolling, should get line 1-25...\n", 0, 15);
    // Since no sleep function is implemented I will temporarily juse use a busy loop
    for (int i = 0; i < 1000000000; i++) {
        i = i + 1;
        i = i - 1;
    }
    monitor_write("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", 0, 15);
}