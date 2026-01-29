#include "libasm.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

/* Macros pour simplifier l'affichage et réduire le code */
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define TEST(name) printf(CYAN "\n=== %s ===\n" RESET, name)

void check_strlen() {
    TEST("FT_STRLEN");
    const char *long_str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    
    // Test 1: Empty string
    printf("Empty:   libc=%zu | asm=%zu\n", strlen(""), ft_strlen(""));
    // Test 2: Long string
    printf("Long:    libc=%zu | asm=%zu\n", strlen(long_str), ft_strlen(long_str));
}

void check_strcpy() {
    TEST("FT_STRCPY");
    char d1[200], d2[200];
    const char *long_str = "Une phrase très longue pour tester le buffer overflow et la copie correcte.";

    // Test 1: Empty string
    printf("Empty:   libc='%s' | asm='%s'\n", strcpy(d1, ""), ft_strcpy(d2, ""));
    // Test 2: Long string
    printf("Long:    libc='%s' | asm='%s'\n", strcpy(d1, long_str), ft_strcpy(d2, long_str));
}

void check_strcmp() {
    TEST("FT_STRCMP");
    //
    printf("Empty/Empty: libc=%d | asm=%d\n", strcmp("", ""), ft_strcmp("", ""));
    printf("Empty/First: libc=%d | asm=%d\n", strcmp("", "A"), ft_strcmp("", "A"));
    printf("Empty/Secnd: libc=%d | asm=%d\n", strcmp("A", ""), ft_strcmp("A", ""));
    printf("Equal:       libc=%d | asm=%d\n", strcmp("Hello", "Hello"), ft_strcmp("Hello", "Hello"));
    printf("Diff:        libc=%d | asm=%d\n", strcmp("Hello", "World"), ft_strcmp("Hello", "World"));
}

void check_strdup() {
    TEST("FT_STRDUP");
    char *s1, *s2;
    const char *long_str = "Test d'allocation dynamique avec une chaine assez longue.";

    // Test 1: Empty string
    s1 = strdup(""); s2 = ft_strdup("");
    printf("Empty:   libc='%s' | asm='%s'\n", s1, s2);
    free(s1); free(s2); // Toujours free

    // Test 2: Long string
    s1 = strdup(long_str); s2 = ft_strdup(long_str);
    printf("Long:    libc='%s' | asm='%s'\n", s1, s2);
    free(s1); free(s2);
}

void check_write() {
    TEST("FT_WRITE");
    int fd = open("test_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    // Test 1: Stdout
    printf("[STDOUT] "); fflush(stdout);
    ft_write(1, "Test\n", 5);
    
    // Test 2: File Open
    ft_write(fd, "File test", 9);
    printf("Write to file 'test_write.txt': OK\n");
    close(fd);

    // Test 3: Wrong FD & Return Value & Errno
    errno = 0;
    int ret = ft_write(-1, "Fail", 4);
    printf("Bad FD:  ret=%d | errno=%d (Expected -1 | 9)\n", ret, errno);
}

void check_read() {
    TEST("FT_READ");
    char buf[100];
    int fd = open("test_write.txt", O_RDONLY); // On réutilise le fichier créé par write

    // Test 1: Open File
    int ret = ft_read(fd, buf, 9);
    buf[ret] = '\0';
    printf("File:    ret=%d | content='%s'\n", ret, buf);
    close(fd);

    // Test 2: Wrong FD & Return Value
    errno = 0;
    ret = ft_read(-1, buf, 10);
    printf("Bad FD:  ret=%d | errno=%d (Expected -1 | 9)\n", ret, errno);

    // Test 3: Stdin
    printf(CYAN "Test Stdin (Type something + Enter): " RESET); fflush(stdout);
    ret = ft_read(0, buf, 99);
    if (ret > 0) buf[ret - 1] = 0; // Enlever le newline pour l'affichage
    printf("Stdin:   read='%s'\n", buf);
}

int main() {
    check_strlen();
    check_strcpy();
    check_strcmp();
    check_strdup();
    check_write();
    check_read();
    return (0);
}