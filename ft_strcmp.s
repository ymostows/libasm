global ft_strcmp

ft_strcmp:
.loop:
    mov     al, byte [rdi]      ; Charge char de s1 dans al
    mov     dl, byte [rsi]      ; Charge char de s2 dans dl
    cmp     al, dl              ; Compare les deux
    jne     .diff               ; S'ils sont différents -> jump vers .diff
    test    al, al              ; Est-ce que c'est la fin de chaine (0) ?
    je      .equal              ; Si on arrive au bout et qu'ils sont égaux -> return 0
    inc     rdi                 ; s1++
    inc     rsi                 ; s2++
    jmp     .loop

.diff:
    movzx   eax, al             ; Convertit al (8 bits) en eax (32 bits) avec des zéros
    movzx   edx, dl             ; Pareil pour dl
    sub     eax, edx            ; Résultat = s1 - s2
    ret

.equal:
    xor     eax, eax            ; return 0
    ret