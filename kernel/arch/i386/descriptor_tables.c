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

void idt_flush(u32int);

static void init_idt();
static void idt_set_gate(u8int, u32int, u16int, u8int);

struct idt_entry idt_entries[256];
struct idt_ptr idt_ptr;

void init_descriptor_tables() {
    init_gdt();
    init_idt();
}

static void init_idt() {
    idt_ptr.limit = sizeof(struct idt_netry) * 256 - 1;
    idt_ptr.base = (u32int) &idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);
    idt_set_gate(0, (u32int) isr0, 0x08, 0x8E);
    idt_set_gate(1, (u32int) isr1, 0x08, 0x8E);
    idt_set_gate(2, (u32int) isr2, 0x08, 0x8E);
    idt_set_gate(3, (u32int) isr3, 0x08, 0x8E);
    idt_set_gate(4, (u32int) isr4, 0x08, 0x8E);
    idt_set_gate(5, (u32int) isr5, 0x08, 0x8E);
    idt_set_gate(6, (u32int) isr6, 0x08, 0x8E);
    idt_set_gate(7, (u32int) isr7, 0x08, 0x8E);
    idt_set_gate(8, (u32int) isr8, 0x08, 0x8E);
    idt_set_gate(9, (u32int) isr9, 0x08, 0x8E);
    idt_set_gate(10, (u32int) isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32int) isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32int) isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32int) isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32int) isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32int) isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32int) isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32int) isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32int) isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32int) isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32int) isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32int) isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32int) isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32int) isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32int) isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32int) isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32int) isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32int) isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32int) isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32int) isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32int) isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32int) isr31, 0x08, 0x8E);

    idt_flush((u32int) &idt_ptr);
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags) {
    struct idt_entry *entry = idt_entries[num];
    entry.base_lo = base & 0xFFFF;
    entry.base_hi = (base >> 16) & 0xFFFF;
    entry.sel = sel;
    entry.always0 = 0;

    // uncomment the OR below when we get to use user-mode. It
    // sets the int gate's priv level to 3 (currently ring level 0)
    entry.flags = flags; /* | 0x60; */
}
