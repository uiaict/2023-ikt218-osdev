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
    if ((strcmp(buffer, "") == 0)) {
        printf("\n");
    }
    else if (strcmp(buffer, "test") == 0) {
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
    }
    else {
        printf("Command not found: ");
        printf(buffer);
    }
    printf("\n");
    resetBuffer();
}