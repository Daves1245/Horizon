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

// This gets called from our ASM interrupt handler stub.
void isr_handler(struct registers regs) {
    terminal_writestring("received interrupt: ");
    printf("int_no: %d err_code: %d", regs.int_no, regs.err_code);
    terminal_scroll();
    terminal_write_dec(regs.int_no);
    terminal_putchar('\n');
}
