// initialises the GDT and IDT, and defines the 
// default IRS and IRQ handler.
// Based on code from Bran's kernel development tutorials
// Rewritten for JamesM's kernel development tutorials

#include "common.h"
#include "descriptor_tables.h"

// access asm functions from C (???? used redundant extern?)
void gdt_flush(u32int);

// internal functions (??)
static void init_gdt();
static void gdt_set_gate(s32int, u32int, u32int, u8int, u8int);

struct gdt_entry gdt_entries[5];
struct gdt_ptr gdt_ptr;
struct idt_entry idt_entries[256];
struct idt_ptr idt_ptr;

void init_descriptor_tables() {
    init_gdt();
}

static void init_gdt() {
    gdt_ptr.limit = sizeof(struct gdt_entry) * 5 - 1;
    gdt_ptr.base = (u32int) &gdt_entries;

    #define HIGH 0xFFFFFFFF

    gdt_set_gate(0, 0, 0, 0, 0); // null segment
    gdt_set_gate(1, 0, HIGH, 0x9A, 0xCF); // code segment
    gdt_set_gate(2, 0, HIGH, 0x92, 0xCF); // data segment
    gdt_set_gate(3, 0, HIGH, 0xFA, 0xCF); // user mode code segment
    gdt_set_gate(4, 0, HIGH, 0xF2, 0xCF); // user mode data segment

    gdt_flush((u32int) &gdt_ptr);
}

// set the value of one gdt entry
static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int limit, u8int access, u8int gran) {
    gdt_entries[num].base_low = base & 0xFFFF;
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = limit & 0xFFFF;
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = access;
}
