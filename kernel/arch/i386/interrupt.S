; x86 assumes unqiue handlers for each of the 32 interrupts. for that reason,
; no additional information is given when a handler is called. this
; tutorial takes the approach of creating a single handler, by standardizing
; stack frames for all handlers (the only difference is some [8, 10-14] interrupts include error codes)
; personally, this seems like a terribly hacky approach with a lot of room
; for bugs (several other lines of code have also been suspect), but will
; work for now until everything is functional and we can go back for cleanup

%macro ISR_NOERRCODE 1 ; takes 1 parameter
; use '%n' to access n'th parameter
    [GLOBAL isr%1] ; ok, this macro feature is p cool
    isr%1:
        cli
        push bye 0 ; push dummy value if it doesn't push its own
        push byte %1 ; push the interrupt number
        jmp isr_common_stub ; go to common handler
%endmacro

%macro ISR_ERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0   ; 0
ISR_NOERRCODE 1   ; 1
ISR_NOERRCODE 2   ; 2
ISR_NOERRCODE 3   ; 3
ISR_NOERRCODE 4   ; 4
ISR_NOERRCODE 5   ; 5
ISR_NOERRCODE 6   ; 6
ISR_NOERRCODE 7   ; 7
ISR_ERRCODE 8   ; 8
ISR_NOERRCODE 9   ; 9
ISR_ERRCODE 10  ; 10
ISR_ERRCODE 11  ; 11
ISR_ERRCODE 12  ; 12
ISR_ERRCODE 13  ; 13
ISR_ERRCODE 14  ; 14
ISR_NOERRCODE 05  ; 15
ISR_NOERRCODE 06  ; 16
ISR_NOERRCODE 07  ; 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

[EXTERN isr_handler]

; This is our common isr stub. it saves the processor state, sets
; up for kernel mode segments, calls C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha               ; pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

    mov ax, ds          ; lower 16 bits eax = ds
    push eax            ; save the data segment descriptor

    mov ax, 0x10        ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx             ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                ; pops edi, esi, ebp...
    add esp, 8          ; cleans pushed error code and pushed isr number
    sti
    iret                ; pops cs, eip, eflags, ss, and esp
