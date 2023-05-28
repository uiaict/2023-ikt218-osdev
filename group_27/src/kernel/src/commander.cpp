#include "printing.h"
#include "system.h"
#include "monitor.h"

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
    buffer[bufLen] = '\0';
    bufLen -= 1;
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
        printf("\nYay!\n");
    }
    else {
        printf("\nCommand not found\n");
    }
    printf(buffer);
    resetBuffer();
}