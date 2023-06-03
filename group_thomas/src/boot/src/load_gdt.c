#include <stdio.h>

void load_gdt(uint32_T);


int main() {
    load_gdt();
    short* screen = (short*) 0xB8000;
    char* message = "Hello";
    char color = 0x0F;

for (int i = 0; i < 5; i++) {
    screen[i] = (color << 8) | message[i];
}
}
