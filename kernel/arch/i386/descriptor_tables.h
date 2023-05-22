// the value of one GDT entry.
// use packed attribute to suggest GCC not add padding
// and align members of the struct.

struct gdt_entry {
    u16int limit_low; // lower 16 bits of limit
    u16int base_low;
    u8int base_middle;
    u8int access;
    u8int granularity;
    u8int base_high;
} __attribute__((packed));

struct gdt_ptr {
    u16int limit; // upper 16 bits of all selector limits
    u32int base; // address of first gdt_entry struct
} __attribute__((packed));

void init_descriptor_tables();
