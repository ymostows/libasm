section .text
global ft_read
extern __errno_location

ft_read:
    xor     eax, eax            ; syscall read = 0
    syscall
    test    rax, rax
    jns     .ok

    mov     edx, eax
    neg     edx

    call    __errno_location wrt ..plt
    mov     dword [rax], edx
    mov     rax, -1
.ok:
    ret
