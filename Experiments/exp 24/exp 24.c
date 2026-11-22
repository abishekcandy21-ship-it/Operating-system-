/* Exp 24: UNIX system calls for file management
   (creat, open, write, lseek, read, close, unlink) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int fd;
    char buffer[100];
    ssize_t bytesRead;

    fd = creat("sample.txt", S_IRWXU);           /* create a new file */
    if (fd == -1) { perror("creat"); exit(1); }
    printf("File 'sample.txt' created successfully.\n");
    close(fd);

    fd = open("sample.txt", O_WRONLY | O_APPEND);
    if (fd == -1) { perror("open"); exit(1); }
    printf("File 'sample.txt' opened for writing.\n");
    write(fd, "Hello, World!\n", 14);
    printf("Data written to 'sample.txt'.\n");
    close(fd);

    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) { perror("open"); exit(1); }
    printf("File 'sample.txt' opened for reading.\n");
    bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) { perror("read"); exit(1); }
    printf("Data read from 'sample.txt':\n");
    write(STDOUT_FILENO, buffer, bytesRead);

    lseek(fd, 7, SEEK_SET);                      /* move to offset 7 */
    bytesRead = read(fd, buffer, 5);
    printf("After lseek(fd, 7, SEEK_SET), 5 bytes read: ");
    write(STDOUT_FILENO, buffer, bytesRead);
    printf("\n");
    close(fd);

    if (unlink("sample.txt") == -1) { perror("unlink"); exit(1); }
    printf("File 'sample.txt' deleted.\n");
    return 0;
}
