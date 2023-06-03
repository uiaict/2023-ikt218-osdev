// memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

typedef struct Block {
  size_t size;
  struct Block* next;
} Block;

#define BLOCK_SIZE sizeof(Block)

void init_memory();
void* malloc(size_t size);
void free(void* ptr);
int print_int(char* buffer, int value);

#endif // MEMORY_H
