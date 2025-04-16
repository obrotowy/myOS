; bool check_cpuid()
global check_cpuid_availability
global cpuid_get_vendor

extern tty_puts

check_cpuid_availability:
    pushfd                               ;Save EFLAGS
    pushfd                               ;Store EFLAGS
    xor dword [esp],0x00200000           ;Invert the ID bit in stored EFLAGS
    popfd                                ;Load stored EFLAGS (with ID bit inverted)
    pushfd                               ;Store EFLAGS again (ID bit may or may not be inverted)
    pop eax                              ;eax = modified EFLAGS (ID bit may or may not be inverted)
    xor eax,[esp]                        ;eax = whichever bits were changed
    popfd                                ;Restore original EFLAGS
    test eax,0x00200000                   ;eax = zero if ID bit can't be changed, else non-zero
    setne al
    ret

cpuid_get_vendor:
    push ebp
    mov ebp, esp
    sub esp, 13
    xor eax, eax
    cpuid
    mov [esp], ebx
    mov [esp+4], edx
    mov [esp+8], ecx
    mov byte [esp+12], 0xa
    push esp
    call tty_puts
    add esp, 4
    mov esp, ebp
    pop ebp
    ret