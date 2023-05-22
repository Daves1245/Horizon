#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"

struct page {
    u32int present   : 1; // page present in memory
    u32int rw        : 1; // read-only if clear, readwrite if set
    u32int user      : 1; // supervisor level only if clear
    u32int accesssed : 1; // page was accessed since last refresh
    u32int dirty     : 1; // page was written to since last refresh
    u32int unused    : 7; // amalgamation of unused and reserved bits
    u32int frame     : 20; // frame address (shifted right 12 bits)
};

struct page_table {
    struct page pages[1024];
}

typedef struct page_directory {
    // array of pointers
    struct page_table *tables[1024];

    // array of pointers to physical location of above map,
    // loaded into CR3 to enable paging
    u32int tablesPhysical[1024];

    u32int physicalAddr;
} page_directory_t;

// set up environment, page directories, enable paging
void init_paging();

// load this new page directory into CR3
void switch_page_directory(page_directory *new);

// get a pointer to the page (at or containing?) addr
// if make, then create the page if necessary
struct page *get_page(u32int addr, int make, page_directory_t *dir);

// page fault handler
void page_fault(registers_t regs);
#endif
