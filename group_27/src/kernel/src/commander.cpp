#include "system.h"
#include "monitor.h"
#include <song/song.h>

extern "C"{
    #include "memory.h"
}

char buffer[80] = {0};
int bufLen = 0;

void increase_buffer(char c) {
    buffer[bufLen] = c;
    bufLen += 1;
}

void decrease_buffer() {
    bufLen -= 1;
    buffer[bufLen] = '\0';
    char a[80] = {*buffer};
}

char get_buffer() {
    return *buffer;
}

char reset_buffer() {
    bufLen = 0;
    mymemset(buffer, '\0', 80);
}

void run_command() {
    if (strcmp(buffer, "test") == 0) {
        // This will only run once because the buffer is never reset because of memory stuff
        printf("UIA OS up and running successfully");
    }
    else if (strcmp(buffer, "clear") == 0) {
        monitor_clear();
    }
    else if (strcmp(buffer, "help") == 0) {
        printf("\nCommands: ");
        printf("\nclear");
        printf("\ntest");
        printf("\nmario");
        printf("\nlogo");
        printf("\nred");
        printf("\nblue");
    }
    else if (strcmp(buffer, "mario") == 0) {
        Song* song = new Song(music_1, sizeof(music_1) / sizeof(Note));

        SongPlayer* player = create_song_player();

        printf("Playing Song...\n");
        player->play_song(song);
        printf("Finished playing the song.\n");
        set_prefix("> ");
        reset_buffer();
        return;
    }
    else if (strcmp(buffer, "red") == 0) {
        monitor_setcolor(4);
        printf("Set color to red, type \"reset\" to reset");
    }
    else if (strcmp(buffer, "blue") == 0) {
        monitor_setcolor(1);
        printf("Set color to blue, type \"reset\" to reset");
    }
    else if (strcmp(buffer, "reset") == 0) {
        monitor_setcolor(7);
        printf("Colour reset");
    }
    else if (strcmp(buffer, "logo") == 0) {
        print_logo();
    }
    else {
        if ((strcmp(buffer, "") != 0)) {
            printf("Command not found: ");
            printf(buffer);
        } else {
            set_prefix("> ");
            reset_buffer();
            return;
        }
    }
    set_prefix("\n> ");
    reset_buffer();
}