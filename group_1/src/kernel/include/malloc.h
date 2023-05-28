#ifndef MALLOC_H
#define MALLOC_H


#include <stdint.h>

//The contents of this file are fetched from the
// "Assignment files" of assignment 4.

// Except this one
typedef uint32_t size_t;

// Initialize the kernel memory manager
void init_kernel_memory(uint32_t* kernel_end);


// Print the current memory layout
void print_memory_layout();


// Free a block of memory
void free(void *mem);


// Free a block of page-aligned memory
void pfree(void *mem);


// Allocate a block of page-aligned memory
char* pmalloc(size_t size);


// Allocate a block of memory
void* my_malloc(size_t size);
/*
 * This is a header file for a simple memory management library.
 * It includes declarations for functions related to memory allocation,
 * paging and memory manipulation (copying and setting).
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h> /* Include standard integer types */
#include <stddef.h> /* Include standard definitions */

/*
 * Definition of a struct that represents a memory allocation.
 * It contains a status field (0 or 1) indicating if the memory
 * is currently allocated or not, and a size field indicating
 * the size of the allocated memory in bytes.
 */
typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

/* Init Kernel Memory */
void init_kernel_memory(uint32_t* kernel_end);


/* Function declarations for paging operations */
extern void init_paging(); /* Initializes paging */
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); /* Maps a virtual address to a physical address */

/* Function declarations for memory allocation */
extern char* pmalloc(size_t size); /* Allocates memory of given size with page alignment */
extern void* my_malloc(size_t size); /* Allocates memory of given size */
extern void free(void *mem); /* Frees memory previously allocated */

/* Function declarations for memory manipulation */
extern void* memcpy(void* dest, const void* src, size_t num ); /* Copies num bytes from src to dest */
extern void* memset (void * ptr, int value, size_t num ); /* Sets num bytes starting from ptr to value */
extern void* memset16 (void *ptr, uint16_t value, size_t num); /* Sets num bytes starting from ptr to a 16-bit value */

/* Other helper functions*/
void print_memory_layout();

// Function to set a block of memory with a byte value
void* memset (void * ptr, int value, size_t num );

#endif
#endif
