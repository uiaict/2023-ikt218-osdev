#include <stdint.h>
#include <stddef.h> 


typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

/* Init Kernel Memory */
void memory_init(uint32_t* kernel_end);
void memory_print();

/* Function declarations for paging operations */
extern void init_paging(); /* Initializes paging */
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); /* Maps a virtual address to a physical address */

/* Function declarations for memory allocation */
extern char* pmalloc(size_t size); /* Allocates memory of given size with page alignment */
extern void* malloc(size_t size); /* Allocates memory of given size */
extern void free(void *mem); /* Frees memory previously allocated */

/* Function declarations for memory manipulation */
extern void* memcpy(void* dest, const void* src, size_t num ); /* Copies num bytes from src to dest */
extern void* memset (void * ptr, int value, size_t num ); /* Sets num bytes starting from ptr to value */
extern void* memset16 (void *ptr, uint16_t value, size_t num); /* Sets num bytes starting from ptr to a 16-bit value */
extern void paging_enable();
extern void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);
