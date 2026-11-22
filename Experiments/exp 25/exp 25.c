/* Exp 25: UNIX I/O system calls - open, fcntl, lseek, stat, opendir, readdir */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    int fd, flags;
    char buf[50];
    struct stat st;
    DIR *dp;
    struct dirent *entry;

    /* open */
    fd = open("foo.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { printf("Error Number %d\n", errno); perror("Program"); exit(1); }
    printf("open  : fd = %d\n", fd);
    write(fd, "0123456789ABCDEFGHIJ", 20);

    /* fcntl */
    flags = fcntl(fd, F_GETFL);
    printf("fcntl : file status flags = %d (O_RDWR %s)\n", flags,
           (flags & O_ACCMODE) == O_RDWR ? "set" : "not set");
    fcntl(fd, F_SETFL, flags | O_APPEND);
    printf("fcntl : O_APPEND flag %s\n", (fcntl(fd, F_GETFL) & O_APPEND) ? "enabled" : "not enabled");

    /* lseek */
    printf("lseek : current offset = %ld\n", (long)lseek(fd, 0, SEEK_CUR));
    lseek(fd, 10, SEEK_SET);
    int n = read(fd, buf, 5);
    buf[n] = '\0';
    printf("lseek : 5 bytes read from offset 10 = %s\n", buf);
    printf("lseek : file size from SEEK_END = %ld\n", (long)lseek(fd, 0, SEEK_END));
    close(fd);

    /* stat */
    if (stat("foo.txt", &st) == 0) {
        printf("stat  : size = %ld bytes, inode = %ld, links = %ld, mode = %o\n",
               (long)st.st_size, (long)st.st_ino, (long)st.st_nlink, st.st_mode & 0777);
        printf("stat  : regular file? %s\n", S_ISREG(st.st_mode) ? "yes" : "no");
    }

    /* opendir / readdir */
    dp = opendir(".");
    if (dp == NULL) { perror("opendir"); exit(1); }
    printf("\nopendir/readdir - files in the current directory:\n");
    while ((entry = readdir(dp)) != NULL)
        printf("  %s\n", entry->d_name);
    closedir(dp);
    return 0;
}
