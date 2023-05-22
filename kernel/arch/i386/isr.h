// isr.h -- interface and structures for high level interrupt service routines

#include "common.h"

struct registers {
    u32int ds; // data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
    u32int int_no, err_code;        // interrupt number and error code (if applicable)
    u32int eip, cs, eflags, useresp, ss; // pushed by the processor automatically
};
