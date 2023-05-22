#include "kheap.h"

u32int placement_address;

u32int kmalloc_a(u32int sz) {
    u32int ret = placement_address;
    if (placement_address & 0xFFFFF000) {
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    return kmalloc(sz);
}

u32int kmalloc_p(u32int sz, u32int *phys) {
    *phys = placement_address;
    return kmalloc(sz);
}

u32int kmalloc_ap(u32int sz, u32int *phys) {
    if (placement_address & 0xFFFFF000) {
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    *phys = placement_address;
    return kmalloc(sz);
}

u32int kmalloc(u32int sz) {
    u32int ret = placement_address;
    placement_address += sz;
    return ret;
}
