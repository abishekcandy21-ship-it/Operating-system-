/* Exp 40: File access permissions and types of users (owner, group, others)
   in Linux - creating a file, viewing and changing permissions with chmod() */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void showPermissions(const char *file)
{
    struct stat st;
    if (stat(file, &st) == -1) { perror("stat"); exit(1); }
    printf("  Owner  : %c%c%c\n", (st.st_mode & S_IRUSR) ? 'r' : '-',
           (st.st_mode & S_IWUSR) ? 'w' : '-', (st.st_mode & S_IXUSR) ? 'x' : '-');
    printf("  Group  : %c%c%c\n", (st.st_mode & S_IRGRP) ? 'r' : '-',
           (st.st_mode & S_IWGRP) ? 'w' : '-', (st.st_mode & S_IXGRP) ? 'x' : '-');
    printf("  Others : %c%c%c\n", (st.st_mode & S_IROTH) ? 'r' : '-',
           (st.st_mode & S_IWOTH) ? 'w' : '-', (st.st_mode & S_IXOTH) ? 'x' : '-');
    printf("  Octal mode = %o\n", st.st_mode & 0777);
}

int main()
{
    char filename[] = "file.txt";
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    write(fd, "Linux file permission demo\n", 27);
    close(fd);
    printf("File '%s' created with default permissions (0644):\n", filename);
    showPermissions(filename);

    int new_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;   /* rw-rw-r-- */
    if (chmod(filename, new_permissions) == 0)
        printf("\nFile permissions changed successfully to rw-rw-r-- (0664):\n");
    else { perror("chmod"); return 1; }
    showPermissions(filename);

    chmod(filename, S_IRUSR | S_IWUSR | S_IXUSR);                            /* rwx------ */
    printf("\nPermissions changed to rwx------ (0700): only the owner has access:\n");
    showPermissions(filename);

    printf("\nOutput of the equivalent shell command 'ls -l %s':\n", filename);
    fflush(stdout);
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ls -l %s", filename);
    system(cmd);
    return 0;
}
