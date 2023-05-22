[GLOBAL gdt_flush]  ; Let C code call gdt_flush()
gdt_flush:
    mov eax, [esp + 4]  ; get the pointer to gdt, passed as a parameter
    lgdt [eax]          ; Load the new gdt pointer

    mov ax, 0x10        ; 0x10 is the offset in the gdt to our data segment
    mov ds, ax          ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush     ; 0x08 is th eoffset to our code segment: Far jump!
.flush:
    ret

[GLOBAL idt_flush]      ; Let C call idt_flush()
idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret
