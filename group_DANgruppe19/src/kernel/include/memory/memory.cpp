#include "memory.h"

#define MEMORY_SIZE 1024*1024 // or whatever size you need
static uint8_t memory[MEMORY_SIZE];
Block* freeList = reinterpret_cast<Block*>(memory);

void init_memory() {
  freeList->size = MEMORY_SIZE - BLOCK_SIZE;
  freeList->next = NULL;
}

void* malloc(size_t size) {
  Block* prev = NULL;
  for (Block* block = freeList; block != NULL; prev = block, block = block->next) {
    if (block->size >= size) {
      if (block->size > size + BLOCK_SIZE) {
        // Split the block.
        Block* next = reinterpret_cast<Block*>(reinterpret_cast<uint8_t*>(block + 1) + size);
        next->size = block->size - size - BLOCK_SIZE;
        next->next = block->next;
        block->next = next;
        block->size = size;
      }

      if (prev == NULL) {
        freeList = block->next;
      } else {
        prev->next = block->next;
      }
      
      return block + 1;
    }
  }
  return NULL; // Not enough memory.
}

void free(void* ptr) {
  Block* block = (Block*)ptr - 1;
  block->next = freeList;
  freeList = block;
}

int print_int(char* buffer, int value) {
  int size = 0;
  if (value == 0) {
    buffer[size++] = '0';
  } else {
    for (int temp = value; temp > 0; temp /= 10) {
      size++;
    }
    for (int i = size - 1; i >= 0; i--) {
      buffer[i] = '0' + value % 10;
      value /= 10;
    }
  }
  buffer[size] = '\0';
  return size;
}