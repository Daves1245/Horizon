#ifndef KHEAP_H
#define KHEAP_H
u32int kmalloc_a(u32int sz); // page aligned
u32int kmalloc_p(u32int sz, u32int *phys); // returns a physical address
u32int kmalloc_ap(u32int sz, u32int *phys); // page aligned and returns a physical address
u32int kmalloc(u32int sz); // vanilla
#endif
