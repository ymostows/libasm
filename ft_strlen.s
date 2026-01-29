global ft_strlen

ft_strlen:
    xor     rax, rax            ; i = 0. (XOR un truc avec lui-même donne toujours 0)
.loop:
    cmp     byte [rdi + rax], 0 ; Est-ce que str[i] == '\0' ?
                                ; rdi = adresse de la chaine, rax = index i
    je      .done               ; Si oui (Jump if Equal), on va à la fin
    inc     rax                 ; i++
    jmp     .loop               ; On recommence la boucle
.done:
    ret                         ; Retourne rax (qui contient i)
