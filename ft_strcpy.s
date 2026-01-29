global ft_strcpy

ft_strcpy:
    mov     rax, rdi            ; On prépare le retour (rax doit contenir dst)
.loop:
    mov     dl, byte [rsi]      ; On charge le char de src (rsi) dans un petit registre (dl)
    mov     byte [rdi], dl      ; On copie dl vers dst (rdi)
    inc     rsi                 ; src++
    inc     rdi                 ; dst++
    test    dl, dl              ; Est-ce que le char copié était '\0' ?
    jne     .loop               ; Si non (Jump Not Equal), on continue
    ret                         ; Si oui, on retourne rax (qui vaut dst depuis le début)