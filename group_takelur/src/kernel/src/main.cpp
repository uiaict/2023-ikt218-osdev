// Define entry point in asm to prevent C++ mangling
extern "C" {
    #include "common.h"
    #include "system.h"
    #include "monitor.h"
    #include "gdt.h"
    #include "idt.h"
    #include "isr.h"
    #include "irq.h"
    #include "print.h"
    #include "interrupt_tests.h"
    #include "keyboard.h"
    #include "memory.h"
    #include "pit.h"
    #include "song/song.h"
    void kernel_main();
}

// THE FOLLOWING FROM LINE 19 TO 39 ARE FROM ASSIGNMENT FILES:

extern uint32_t end; // This is defined in linker.ld
typedef uint32_t size_t;

// Overload the new operator for single object allocation
void* operator new(size_t size) 
{
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) noexcept 
{
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

// Overload the new operator for array allocation
void* operator new[](size_t size) 
{
    return malloc(size);   // Call the C standard library function malloc() to allocate memory of the given size and return a pointer to it
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) noexcept 
{
    free(ptr);             // Call the C standard library function free() to deallocate the memory pointed to by the given pointer
}

void kernel_main() 
{
    /* INITIALIZATION */
    init_kernel_memory(&end);   // Initialize kernel memory
    init_gdt();                 // Initialize the GDT
    init_idt();                 // Initialize the IDT
    init_interrupt_handlers();  // Initialize interrupt handlers
    init_irq_handlers();        // Initialize IRQ handlers
    asm volatile("sti");        // Enable interrupts
    init_paging();              // Initialize paging
    init_pit();                 // Initialize PIT



    /* MEMORY INFORMATION PRINTS */
    clear_monitor();
    printf("Printing memory layout after initialization\n\n");
    print_memory_layout();      // Print memory layout

    // Allocate some memory using kernel memory manager
    // THIS IS PART OF THE ASSIGNMENT
    void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();
    sleep_interrupt(6000);

    clear_monitor();
    printf("Printing memory layout after after allocation\n\n");
    print_memory_layout();      // Print memory layout

    // Free some memory using kernel memory manager
    free(some_memory);  // Free memory allocated using malloc
    free(memory2);
    free(memory3);
    delete[] memory4;   // Delete because memory was allocated using new[]
    sleep_interrupt(6000);
    
    clear_monitor();
    printf("Printing memory layout after after freeing memory\n\n");
    print_memory_layout();      // Print memory layout
    sleep_interrupt(6000);
    


    /* PRINT TESTS */
    /*
    clear_monitor();
    printf("This should insert string: %s\n", "Hello World!");
    printf("This should insert integer: %d\n", 12345);
    printf("This should insert decimal %d as hex: %x\n", 1452, 1452);
    printf("This should insert percentage char: %%\n");
    sleep_interrupt(6000);
    */



    /* INTERRUPT TESTS
    I have not implementet any actual exception handling. My service routines only print information about which interrupt
    was triggered, and do not handle the fault. These tests therefore only triggers the ISR, and do not create an actual exception.
    */
    /*
    clear_monitor();
    printf("Triggering divide by zero exception...\n");
    test_divide_by_zero();
    printf("Triggering debug exception...\n"); 
    trigger_debug_exception();
    printf("Triggering breakpoint exception...\n");
    trigger_breakpoint_exception();
    printf("Triggering invalid opcode exception...\n");
    trigger_invalid_opcode_exception();
    printf("Triggering unhandled interrupt exception...\n");
    trigger_unhandled_interrupt(); 
    sleep_interrupt(6000);
    */



    /* MONITOR WRITING TESTS (assignment 2) */
    /*
    clear_monitor();
    monitor_write("Welcome to Takelur OS version 0.1!\n", 0, 15);
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
    monitor_write("\nWill now test scrolling, should get line 1-25 in 10 seconds...\n", 0, 15);
    sleep_interrupt(10000);
    monitor_write("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", 0, 15);
    sleep_interrupt(6000);
    */



    /* PIT tests */
    /*
    int counter = 0;    // counter for PIT tests
    while(1)
    {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    }
    */



    /* INITIALIZE SONG PLAYER */
    Song* songs[] = {
        new Song(startup, sizeof(startup) / sizeof(Note)),
        new Song(ground_theme, sizeof(ground_theme) / sizeof(Note)),
        new Song(little_star, sizeof(little_star) / sizeof(Note))
    };
    uint32_t n_songs = sizeof(songs) / sizeof(Song*);
    SongPlayer* player = create_song_player();



    /* WELCOME SCREEN */
    clear_monitor();
    printf("\
                 _____     _        _               ___  ____  \n\
                |_   _|_ _| | _____| |_   _ _ __   / _ \\/ ___| \n\
                  | |/ _` | |/ / _ \\ | | | | '__| | | | \\___ \\ \n\
                  | | (_| |   <  __/ | |_| | |    | |_| |___) |\n\
                  |_|\\__,_|_|\\_\\___|_|\\__,_|_|     \\___/|____/ \n\n");
    printf("Welcome to Takelur's OS version "); monitor_write("0.1!", 4, 15);
    printf("\nYou can now "); monitor_write("type", 0, 2); printf(" on the keyboard and see the characters on the screen.\nYou can try out the "); 
    monitor_write("backspace", 0, 2); printf(", "); monitor_write("tab", 0, 2); printf(", "); monitor_write("shift", 0, 2); printf(", "); 
    monitor_write("caps lock", 0, 2); printf(", and "); monitor_write("AltGr", 0, 2); printf(" keys.\n");
    printf("You can do "); monitor_write("AltGr + c", 0, 4); printf(" to clear the screen.\n\n");
    // Play startup sound
    player->play_song(songs[0]);

    /* UNCOMMENT TO PLAY ALL SONGS ADDED */
    /*
    for(uint32_t i =0; i < n_songs; i++){
        printf("Playing Song...\n");
        player->play_song(songs[i]);
        printf("Finished playing the song.\n");
    }
    */
    


    // While loop to read from keyboard and print to monitor
    while(1)
    {
         char c = keyboard_read();
         if (c != 0)
              printf("%c", c);
    }
}