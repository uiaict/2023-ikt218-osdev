#include <stdbool.h>
#include <stddef.h>
#include "gdt.h"
#include "idt.h"
#include "pit.h"
#include "drivers/keyboard.h"
#include "ports.h"
#include <song/song.h>

// Define entry point in asm to prevent C++ mangling
extern "C"
{
	#include "drivers/screen.h"
	#include "memory/memory_management.h"
    void kernel_main();
}

// Define end to refer to the memory address where kernel memory will start, originally found in linker.ld.
extern uint32_t end;

// Overload the new operator for single object allocation
void* operator new(size_t size) {
    return malloc(size);
}

// Overload the new operator for array allocation
void* operator new[](size_t size) {
    return malloc(size);
}

// Overload the delete operator for single object deallocation
void operator delete(void* ptr) {
    free(ptr);
}

// Overload the delete operator for array deallocation
void operator delete[](void* ptr) {
    free(ptr);
}

void kernel_main() 
{
	//Initialize the kernel memory manager with the end of the kernel image.
	init_kernel_memory(&end);
	//Initialize the Global Descriptor Table.
    init_gdt();
	//Initialize the Interrupt Descriptor Table.
	init_idt();
	//Initialize the keyboard.
	init_keyboard();
	asm volatile("sti");
	//Initialize paging.
	init_paging();
	//Print memory layout.
	print_memory_layout();
	//Initialize the System Timer
	init_pit();

	void* some_memory = malloc(12345); 
    void* memory2 = malloc(54321); 
    void* memory3 = malloc(13331);
    char* memory4 = new char[1000]();

	/*
	int counter = 0;
	while(true)
	{
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
 	};
	*/

	
	Song* songs[] = {
        new Song(music_1, sizeof(music_1) / sizeof(Note)),
        new Song(music_6, sizeof(music_6) / sizeof(Note)),
        new Song(music_5, sizeof(music_5) / sizeof(Note)),
        new Song(music_4, sizeof(music_4) / sizeof(Note)),
        new Song(music_3, sizeof(music_3) / sizeof(Note)),
        new Song(music_2, sizeof(music_2) / sizeof(Note))
    };
    uint32_t n_songs = sizeof(songs) / sizeof(Song*);

    SongPlayer* player = create_song_player();


    while(true){
	    for(uint32_t i =0; i < n_songs; i++){
	        printf("Playing Song...\n");
	        player->play_song(songs[i]);
	        printf("Finished playing the song.\n");
	    }
    };
	
	
	while(1){}
} 