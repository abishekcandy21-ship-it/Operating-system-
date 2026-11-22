/* Exp 2: Copy the content of one file to another using the
   open(), read(), write() and close() system calls */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main()
{
    char src[100], dest[100], buffer[BUF_SIZE];
    int fd1, fd2;
    ssize_t n;

    printf("Enter the source file name: ");
    scanf("%s", src);
    printf("Enter the destination file name: ");
    scanf("%s", dest);

    fd1 = open(src, O_RDONLY);
    if (fd1 < 0) {
        perror("Cannot open source file");
        exit(1);
    }
    fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("Cannot open destination file");
        exit(1);
    }

    while ((n = read(fd1, buffer, BUF_SIZE)) > 0)
        write(fd2, buffer, n);

    close(fd1);
    close(fd2);
    printf("Contents copied from %s to %s\n", src, dest);
    return 0;
}
