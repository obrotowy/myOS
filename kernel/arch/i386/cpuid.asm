; bool check_cpuid()
global check_cpuid_availability
global cpuid_get_vendor
global get_ebx
global get_cr0
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
    push edi
    push ebx
    xor eax, eax
    cpuid
    mov edi, [ebp+8]
    mov [edi], ebx
    mov [edi+4], edx
    mov [edi+8], ecx
    mov byte [edi+12], 0
    pop ebx
    pop edi
    mov esp, ebp
    pop ebp
    ret

get_cr0:
    mov eax, cr0
    ret

get_ebx:
    mov eax, ebx
    ret