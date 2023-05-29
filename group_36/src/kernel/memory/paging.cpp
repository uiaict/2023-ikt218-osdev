#include "paging.h"
#include "memory.h"
#include "../../stdlib/stdlib/cpp/bitset.h"
#include "../../stdlib/stdlib/cpp/exception.h"
#include "../../boot/include/boot.h"
#include "../include/print.h"

void init_paging()
{
    UiAOS::Memory::Paging(0x1000000);
}

UiAOS::Memory::Paging::Paging(uint32_t mem_end_page)
: frames(mem_end_page, mem_end_page / 0x100)
{
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
    CPU::ISR::register_interrupt_handler(ISR14, [](CPU::ISR::registers_t* regs, void* ctx){
        UiAOS::Memory::Paging::page_fault(regs, ctx);
    }, static_cast<void*>(this));

    switch_page_directory(kernel_directory);
    enable_paging();
}

bool UiAOS::Memory::Paging::set_directory(UiAOS::Memory::PageDirectory *dir) {
    // UiAOS::IO::Monitor::print_string("[set-directory] ");
    // UiAOS::IO::Monitor::print_hex(reinterpret_cast<uint32_t>(current_directory));
    // UiAOS::IO::Monitor::print_string(" => ");
    // UiAOS::IO::Monitor::print_hex(reinterpret_cast<uint32_t>(dir));
    // UiAOS::IO::Monitor::print_new_line();
    printf("[set-directory] ");
    print_hex(reinterpret_cast<uint32_t>(current_directory));
    current_directory = dir;
    return false;
}

void UiAOS::Memory::Paging::enable_paging() {
    uint32_t cr0; // Define pointer to cr0
    asm volatile("mov %%cr0, %0": "=r"(cr0)); // Move cr0 register to our cr0 pointer
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0)); // Update cr0 with our cr0 data pointer
}

void UiAOS::Memory::Paging::switch_page_directory(UiAOS::Memory::PageDirectory *dir) {
    set_directory(dir);
    asm volatile("mov %0, %%cr3":: "r"(&current_directory->tables_physical)); // Move page directory to cr3 register
}

void UiAOS::Memory::Paging::page_fault(UiAOS::CPU::ISR::registers_t* regs, void*)
{
    uint32_t faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

    int present   = !(regs->err_code & 0x1); // Page not present
    auto rw = regs->err_code & 0x2;           // Write operation?
    auto us = regs->err_code & 0x4;           // Processor was in user-mode?
    auto reserved = regs->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    auto id = regs->err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    // UiAOS::IO::Monitor::print_string("Page fault! ( ");
    // if (present) {UiAOS::IO::Monitor::print_string("present ");}
    // if (rw) {UiAOS::IO::Monitor::print_string("read-only ");}
    // if (us) {UiAOS::IO::Monitor::print_string("user-mode ");}
    // if (reserved) {UiAOS::IO::Monitor::print_string("reserved ");}
    // UiAOS::IO::Monitor::print_string(") at 0x");
    // UiAOS::IO::Monitor::print_hex(faulting_address);
    // UiAOS::IO::Monitor::print_new_line();
    // PANIC("Page fault");
}


bool UiAOS::Memory::Page::alloc_frame(uint32_t idx , int is_kernel, int is_writeable)
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
        }

        present = 1; // Mark it as present.
        rw = (is_writeable)?1:0; // Should the page be writeable?
        user = (is_kernel)?0:1; // Should the page be user-mode?
        frame = idx;
    }

    return true;
}

bool UiAOS::Memory::Page::free_frame()
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

UiAOS::Memory::Page* UiAOS::Memory::PageDirectory::get_page(uint32_t address, int make)
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