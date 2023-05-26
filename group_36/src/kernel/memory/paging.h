#ifndef UIAOS_PAGING_H
#define UIAOS_PAGING_H

#include "stdint.h"
#include "../../stdlib/stdlib/cpp/bitset.h"
#include "../cpu/include/cpu.h"
#include "kmalloc.h"
#include "../../stdlib/stdlib/cpp/bitset.h"


void init_paging() asm ("init_paging");

#define NUM_PAGES 1024

namespace UiAOS::Memory {
    class Page {
    public:
        uint32_t present: 1;   // Page present in memory
        uint32_t rw: 1;   // Read-only if clear, readwrite if set
        uint32_t user: 1;   // Supervisor level only if clear
        uint32_t accessed: 1;   // Has the page been accessed since last refresh?
        uint32_t dirty: 1;   // Has the page been written to since last refresh?
        uint32_t unused: 7;   // Amalgamation of unused and reserved bits
        uint32_t frame: 20;  // Frame address (shifted right 12 bits)

        bool alloc_frame(uint32_t idx, int is_kernel, int is_writeable);

        bool free_frame();
    };

    class PageTable {
    public:
        Page pages[NUM_PAGES];
    };

    class PageDirectory {
    public:
        PageTable *tables[NUM_PAGES];
        uint32_t tables_physical[NUM_PAGES];

        Page *get_page(uint32_t address, int make);
    };

    class Paging{
        UiAOS::std::Bitset frames;

        PageDirectory *kernel_directory = nullptr;

        PageDirectory *current_directory = nullptr;

        void switch_page_directory(UiAOS::Memory::PageDirectory *dir);
        static void page_fault(UiAOS::CPU::ISR::registers_t* regs, void*);

        bool set_directory(UiAOS::Memory::PageDirectory* dir);

    public:
        explicit Paging(uint32_t mem_page_end);


        void enable_paging();
    };
    void page_fault(UiAOS::CPU::ISR::registers_t *regs, void *);
}

#endif //UIAOS_PAGING_H
