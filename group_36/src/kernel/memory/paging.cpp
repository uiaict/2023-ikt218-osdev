#include "paging.h"
#include "memory.h"
#include "../../stdlib/stdlib/cpp/bitset.h"
#include "../../stdlib/stdlib/cpp/exception.h"
#include "../../boot/include/boot.h"
#include "../include/print.h"

void init_paging()
{

    Paging(0x1000000);
}

Paging::Paging(uint32_t mem_end_page)
: frames(mem_end_page, mem_end_page / 0x100)
{
    // printf("\n");
    // print_int(reinterpret_cast<uint32_t>(this));
    // printf("\n");
    // print_int(reinterpret_cast<uint32_t>(this+sizeof(Paging)));
    // printf("\n");

    kernel_directory = (PageDirectory*)kmalloc_a(sizeof(PageDirectory));
    memset(kernel_directory, 0, sizeof(PageDirectory));

    int i = 0;
    while (i < placement_address)
    {
        uint32_t idx = frames.first_available_frame();
        if(kernel_directory->get_page(i, 1)->alloc_frame(idx, 0, 0)){
            frames.set_frame(idx);
        }
        i += 0x1000;
    }
    register_interrupt_handler(ISR14, [](registers_t* regs, void* ctx){
        Paging::page_fault(regs, ctx);
    }, static_cast<void*>(this));

    switch_page_directory(kernel_directory);
    enable_paging();
}

bool Paging::set_directory(PageDirectory *dir) {
    printf("[set-directory] ");
    print_hex(reinterpret_cast<uint32_t>(current_directory));
    printf(" => ");
    print_hex(reinterpret_cast<uint32_t>(dir));
    printf("\n");
    current_directory = dir;
    return false;
}

void Paging::enable_paging() {
    uint32_t cr0; // Define pointer to cr0
    asm volatile("mov %%cr0, %0": "=r"(cr0)); // Move cr0 register to our cr0 pointer
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0)); // Update cr0 with our cr0 data pointer
}

void Paging::switch_page_directory(PageDirectory *dir) {
    set_directory(dir);
    asm volatile("mov %0, %%cr3":: "r"(&current_directory->tables_physical)); // Move page directory to cr3 register
}

void Paging::page_fault(registers_t* regs, void*)
{
    uint32_t faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

    int present   = !(regs->err_code & 0x1); // Page not present
    auto rw = regs->err_code & 0x2;           // Write operation?
    auto us = regs->err_code & 0x4;           // Processor was in user-mode?
    auto reserved = regs->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    auto id = regs->err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    printf("Page fault: '");
    if (present) {printf("present ");}
    if (rw) {printf("read-only ");}
    if (us) {printf("user-mode ");}
    if (reserved) {printf("reserved ");}
    printf("' at 0x");
    print_hex(faulting_address);
    printf("\n");
}


bool Page::alloc_frame(uint32_t idx , int is_kernel, int is_writeable)
{
    if (frame != 0)
    {
        return false; // Frame was already allocated, return straight away.
    }
    else
    {
        if (idx == (uint32_t)-1)
        {
            // PANIC is just a macro that prints a message to the screen then hits an infinite loop.
            // PANIC("There is no free frames!");
            printf("there are no free frames");
        }

        present = 1; // Mark it as present.
        rw = (is_writeable)?1:0; // Should the page be writeable?
        user = (is_kernel)?0:1; // Should the page be user-mode?
        frame = idx;
    }

    return true;
}

bool Page::free_frame()
{
    uint32_t _frame = 0x0;
    if (!(frame = _frame))
    {
        return false; // The given page didn't actually have an allocated frame!
    }
    else
    {
        frame = 0x0; // Page now doesn't have a frame.

    }
    return true;
}

Page* PageDirectory::get_page(uint32_t address, int make)
{
    // Turn the address into an index.
    address /= 0x1000;
    // Find the page table containing this address.
    uint32_t table_idx = address / NUM_PAGES;
    if (tables[table_idx]) // If this table is already assigned
    {
        return &tables[table_idx]->pages[address % NUM_PAGES];
    }
    else if(make)
    {
        uint32_t tmp;
        tables[table_idx] = (PageTable*)kmalloc_ap(sizeof(PageTable), &tmp);
        memset(tables[table_idx], 0, 0x1000);
        tables_physical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &tables[table_idx]->pages[address % NUM_PAGES];
    }
    else
    {
        return nullptr;
    }
}