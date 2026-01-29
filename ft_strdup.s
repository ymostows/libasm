section .text
global ft_strdup

extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
    push    r12
    mov     r12, rdi            ; save s

    mov     rdi, r12
    call    ft_strlen wrt ..plt ; ok (blinde)
    inc     rax                 ; +1 for '\0'

    mov     rdi, rax
    call    malloc wrt ..plt    ; PIE-safe
    test    rax, rax
    je      .null

    mov     rdi, rax            ; dst
    mov     rsi, r12            ; src
    call    ft_strcpy wrt ..plt ; ok (blinde)

    pop     r12
    ret

.null:
    xor     rax, rax
    pop     r12
    ret
