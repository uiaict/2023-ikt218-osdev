#include "printing.h"

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

void runCommand() {
    print("\nCommand not found");
}