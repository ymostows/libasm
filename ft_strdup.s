global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
    push    r12                 ; 1. Sauvegarde r12
    mov     r12, rdi            ; 2. Copie l'argument 'src' dans r12

    mov     rdi, r12            ; Prépare arg pour strlen
    call    ft_strlen wrt ..plt ;
    inc     rax                 ; Ajoute +1 pour le '\0' final

    mov     rdi, rax            ; Prépare arg pour malloc
    call    malloc wrt ..plt    ;
    test    rax, rax            ;
    je      .null

    mov     rdi, rax            ; Arg 1 strcpy (dst)
    mov     rsi, r12            ; Arg 2 strcpy (src)
    call    ft_strcpy wrt ..plt ; Copie la chaîne

    pop     r12                 ; Restaure r12 comme il était au début
    ret                         ; Retourne rax (le pointeur malloc)

.null:
    xor     rax, rax            ; Retourne NULL (0)
    pop     r12                 ; restaurer r12 même en cas d'erreur
    ret