/*
 * High level interrupt service routines and interrupt request handlers.
 * Part of this code is modified from Bran's kernel development tutorials.
 * Rewritten for JamesM's kernel development tutorials.
 *
 */

#include "common.h"
#include "isr.h"
#include <kernel/tty.h>

#include <stdio.h>

int has_err_code(int n) {
    return (n == 8) || ((n >= 10) && (n <= 14));
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(struct registers regs) {
    terminal_writestring("received interrupt: ");
    printf("interrupt: %d ", regs.int_no);
    if (has_err_code(regs.int_no)) {
        printf("err_code: %d", regs.err_code);
    }
    // printf("int_no: %d err_code: %d", regs.int_no, regs.err_code);
    // terminal_scroll();
    terminal_putchar('\n');
}

void isr_0() {}
void isr_1() {}
void isr_2() {}
void isr_3() {}
void isr_4() {}
void isr_5() {}
void isr_6() {}
void isr_7() {}
void isr_8(int errno) {}
void isr_9() {}
void isr_10(int errno) {}
void isr_11(int errno) {}
void isr_12(int errno) {}
void isr_13(int errno) {}
void isr_14(int errno) {}
void isr_15() {}
void isr_16() {}
void isr_17() {}
void isr_18() {}
void isr_19() {}
void isr_20() {}
void isr_21() {}
void isr_22() {}
void isr_23() {}
void isr_24() {}
void isr_25() {}
void isr_26() {}
void isr_27() {}
void isr_28() {}
void isr_29() {}
void isr_30() {}
void isr_31() {}
