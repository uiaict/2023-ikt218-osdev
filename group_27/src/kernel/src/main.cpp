
#include "system.h"
#include "gdt.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void printmyword(char word[50])
{
  uint8_t (*fb)[80][2] = (uint8_t (*)[80][2]) 0xb8000;

  int wordlen = 0;
  while(word[wordlen] != '\0' ){
      wordlen++;
  }

  for(int i = 0; i < wordlen; i++)
  {
    fb[0][i][0]= word[i];   
  }
}

void kernel_main()
{
    printmyword("SHITBIOS (version 69)      ");
}
