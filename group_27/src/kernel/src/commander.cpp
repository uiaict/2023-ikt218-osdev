#include "printing.h"
#include "system.h"
#include "monitor.h"
#include <song/song.h>

extern "C"{
    #include "memory.h"
}

char buffer[80] = {0};
int bufLen = 0;

void increaseBuffer(char c) {
    buffer[bufLen] = c;
    bufLen += 1;
}

void decreaseBuffer() {
    bufLen -= 1;
    buffer[bufLen] = '\0';
    char a[80] = {*buffer};
}

char getBuffer() {
    return *buffer;
}

char resetBuffer() {
    bufLen = 0;
    mymemset(buffer, '\0', 80);
}

void runCommand() {
    if (strcmp(buffer, "test") == 0) {
        // This will only run once because the buffer is never reset because of memory stuff
        printf("UIA OS up and running successfully");
    }
    else if (strcmp(buffer, "pepsi") == 0) {
        printf("Voffvoff");
    }
    else if (strcmp(buffer, "clear") == 0) {
        monitor_clear();
    }
    else if (strcmp(buffer, "help") == 0) {
        printf("\nCommands: ");
        printf("\nclear");
        printf("\ntest");
        printf("\npepsi");
        printf("\nmario");
    }
    else if (strcmp(buffer, "mario") == 0) {
        Song* song = new Song(music_1, sizeof(music_1) / sizeof(Note));

        SongPlayer* player = create_song_player();

        printf("Playing Song...\n");
        player->play_song(song);
        printf("Finished playing the song.\n");
        set_prefix("> ");
        resetBuffer();
        return;
    }
    else {
        if ((strcmp(buffer, "") != 0)) {
            printf("Command not found: ");
            printf(buffer);
        } else {
            set_prefix("> ");
            resetBuffer();
            return;
        }
    }
    set_prefix("\n> ");
    resetBuffer();
}