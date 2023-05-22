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

// describes an interrupt gate
struct idt_entry {
    u16int base_lo;         // lower 16 bits of the addr to jmp to when int is fired.
    u16int sel;             // kernel segment selector
    u8int always0;          // must always be zero
    u8int flags;            // more flags. see manual documentation
    u16int base_hi;        
} __attribute__((packed));

// pointer to array of interrupt (int) handlers
// in format suitable for giving to 'lidt' x86 instruction
struct idt_ptr {
    u16int limit;
    u32int base;            // addr of first element in idt_entry array
} __attribute((packed));

// for access to addresses of asm irs handlers
void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();
void init_descriptor_tables();
