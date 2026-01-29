global ft_write
extern __errno_location         ; Fonction externe pour gérer les erreurs C

ft_write:
    mov     eax, 1              ; ID du syscall write
    syscall                     ; "Eh Linux, fais le travail stp !"
                                ; Linux regarde rax (ID), rdi (fd), rsi (buffer), rdx (count)
    
    test    rax, rax            ; Linux a fini. Il a mis le résultat dans rax.
    jns     .ok                 ; Si rax >= 0 (Jump No Sign), tout va bien, on retourne.

    ; --- Gestion d'erreur (Si rax est négatif) ---
    mov     edx, eax            ; On copie l'erreur (ex: -9) dans edx
    neg     edx                 ; On la rend positive (ex: 9 pour "Bad File Descriptor")
    
    call    __errno_location wrt ..plt ; On demande l'adresse de la variable globale 'errno'
                                       ; 'wrt ..plt' sert à trouver la fonction dans la librairie dynamique
    mov     dword [rax], edx    ; On écrit le code erreur (9) dans la variable errno
    mov     rax, -1             ; On retourne -1 comme demandé par le manuel
.ok:
    ret