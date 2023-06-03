/**
 * @file
 * @brief Simple memory management library.
 * It includes declarations for functions related to memory allocation,
 * paging and memory manipulation (copying and setting).
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Represents a memory allocation. */
struct alloc {
    uint8_t status; /*!< Memory is currently allocated or not (0 or 1). */
    uint32_t size;  /*!< Size of the allocated memory in bytes. */
};

/** Initialize kernel memory */
void kernel_memory_init(const uint32_t *kernel_end);

/** Initializes paging */
void paging_init();

/** Maps a virtual address to a physical address */
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);

/** Allocates memory of given @c size with page alignment */
char *pmalloc(size_t size);

/** Allocates memory of given size */
void *malloc(size_t size);

/** Frees memory previously allocated */
void free(void *mem);

/** Copies @c n bytes from @c src to @c dest */
void *memcpy(void *dest, const void *src, size_t n);

/** Sets @c num bytes starting from @c ptr to @c value */
void *memset(void *ptr, int value, size_t num);

/** Sets @c num bytes starting from @c ptr to a 16-bit @c value */
void *memset16(void *ptr, uint16_t value, size_t num);

void print_memory_layout();


#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H */
