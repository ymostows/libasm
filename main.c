#include "libasm.h"

void test_ft_strlen()
{
    printf("ft_strlen\n");
    char *normal = "Hello !";
    printf("strlen : %zu / ft_strlen : %zu\n", strlen(normal), ft_strlen(normal));

    char *empty = "";
    printf("strlen : %zu / ft_strlen : %zu\n", strlen(empty), ft_strlen(empty));

    char *long_str = malloc(1000001);
    if (long_str)
    {
        memset(long_str, 'a', 1000000);
        long_str[1000000] = '\0';
        printf("strlen : %zu / ft_strlen : %zu\n", strlen(long_str), ft_strlen(long_str));
        free(long_str);
    }
}

void test_ft_strcpy()
{
    printf("\n\nft_strcpy\n");
    char dest_norm[100];
    char *src_norm = "Hello !";
    char *ret_norm = ft_strcpy(dest_norm, src_norm);
    printf("[%s] -> [%s]\n", src_norm, dest_norm);
    printf("Pointer : %s\n", (ret_norm == dest_norm ? "OK" : "KO"));

    char dest_empty[10];
    char *ret_empty = ft_strcpy(dest_empty, "");
    printf("Source [] -> Dest [%s]\n", dest_empty);
    printf("Pointer : %s\n", (ret_empty == dest_empty ? "OK" : "KO"));

    char *long_src = malloc(1000001);
    char *long_dest = malloc(1000001);
    if (long_src && long_dest)
    {
        memset(long_src, 'A', 1000000);
        long_src[1000000] = '\0';
        
        char *ret_long = ft_strcpy(long_dest, long_src);
        
        printf("Long : ");
        if (strlen(long_dest) == 1000000 && long_dest[0] == 'A')
            printf("Success !\n");
        else
            printf("Failure !\n");
        printf("Pointer : %s\n", (ret_long == long_dest ? "OK" : "KO"));
    }
    free(long_src);
    free(long_dest);
    printf("\n");
}

void test_ft_strcmp()
{
    printf("\nft_strcmp\n");

    char *empty = "";
    printf("strcmp : %d / ft_strcmp : %d\n", strcmp(empty, empty), ft_strcmp(empty, empty));

    char *str = "Hello";
    printf("strcmp : %d / ft_strcmp : %d\n", strcmp(empty, str), ft_strcmp(empty, str));
    printf("strcmp : %d / ft_strcmp : %d\n", strcmp(str, empty), ft_strcmp(str, empty));

    char *s1 = "Hello";
    char *s2 = "Hello";
    printf("strcmp : %d / ft_strcmp : %d\n", strcmp(s1, s2), ft_strcmp(s1, s2));

    char *s3 = "Hella";
    printf("strcmp : %d / ft_strcmp : %d\n", strcmp(s1, s3), ft_strcmp(s1, s3));
    printf("strcmp : %d / ft_strcmp : %d\n", strcmp(s3, s1), ft_strcmp(s3, s1));
}

void test_ft_write()
{
    printf("\nft_write\n");
    char *msg = "Hello !";
    int len = strlen(msg);

    printf("write : ");
    fflush(stdout);
    ssize_t r1 = write(1, msg, len);
    printf("\nreturn : %zd\n", r1);

    printf("ft_write : ");
    fflush(stdout);
    ssize_t r2 = ft_write(1, msg, len);
    printf("\nreturn : %zd\n", r2);
    int fd = open("test_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1)
    {
        ssize_t file_ret = ft_write(fd, "File test", 9);
        printf("Open file (fd %d) : ft_write return = %zd\n", fd, file_ret);
        close(fd);
    }

    errno = 0;
    ssize_t err1 = write(-1, msg, len);
    int e1 = errno;

    errno = 0;
    ssize_t err2 = ft_write(-1, msg, len);
    int e2 = errno;
    printf("Error (wrong fd) : write = %zd (errno %d) / ft_write = %zd (errno %d)\n", 
            err1, e1, err2, e2);

    printf("Empty : write = %zd / ft_write = %zd\n", 
            write(1, "", 0), ft_write(1, "", 0));
}

void test_ft_read()
{
    printf("\nft_read\n");
    char buffer1[512];
    char buffer2[512];
    ssize_t r1, r2;

    printf("Stdin test : ");
    fflush(stdout);
    r1 = ft_read(0, buffer1, 511);
    if (r1 >= 0) buffer1[r1] = '\0';
    printf("return : %zd | content : %s\n", r1, buffer1);

    int fd = open("test_write.txt", O_RDONLY);
    if (fd != -1)
    {
        memset(buffer1, 0, 512);
        memset(buffer2, 0, 512);
        
        r1 = read(fd, buffer1, 12);
        lseek(fd, 0, SEEK_SET);
        r2 = ft_read(fd, buffer2, 12);
        
        printf("read    : %zd / buffer : [%s]\n", r1, buffer1);
        printf("ft_read : %zd / buffer : [%s]\n", r2, buffer2);
        close(fd);
    }

    errno = 0;
    ssize_t err1 = read(-1, buffer1, 10);
    int e1 = errno;

    errno = 0;
    ssize_t err2 = ft_read(-1, buffer2, 10);
    int e2 = errno;
    printf("Error (wrong fd) : read = %zd (errno %d) / ft_read = %zd (errno %d)\n", 
            err1, e1, err2, e2);

    printf("Empty : read = %zd / ft_read = %zd\n", 
            read(1, buffer1, 0), ft_read(1, buffer2, 0));
}

void test_ft_strdup()
{
    printf("\nft_strdup\n");

    char *empty = "";
    char *r1 = ft_strdup(empty);
    printf("Empty : original [%s] / copy [%s]\n", empty, r1);
    printf("Different pointers ? %s\n", (r1 != empty ? "YES" : "NO"));
    free(r1);

    char *norm = "Hello !";
    char *r2 = ft_strdup(norm);
    printf("Normal : original [%s] / copy [%s]\n", norm, r2);
    free(r2);

    char *long_str = malloc(1000001);
    if (long_str)
    {
        memset(long_str, 'Z', 1000000);
        long_str[1000000] = '\0';
        
        char *r3 = ft_strdup(long_str);
        
        printf("Long : ");
        if (r3 && strlen(r3) == 1000000 && r3[0] == 'Z')
            printf("Success !\n");
        else
            printf("Failure !\n");
            
        free(long_str);
        free(r3);
    }
}

int main(void)
{
    test_ft_strlen();
    test_ft_strcpy();
    test_ft_strcmp();
    test_ft_write();
    test_ft_read();
    test_ft_strdup();
    return (0);
}