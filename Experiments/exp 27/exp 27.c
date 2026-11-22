/* Exp 27: Simulating the UNIX 'ls' command
   Usage: ./a.out [-l] [directory]  (hidden files are not shown) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>

int cmp(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

void printLong(const char *dir, const char *name)
{
    char path[512], perm[11], tbuf[30];
    struct stat st;
    snprintf(path, sizeof(path), "%s/%s", dir, name);
    if (stat(path, &st) == -1) return;

    perm[0] = S_ISDIR(st.st_mode) ? 'd' : '-';
    perm[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    perm[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
    perm[10] = '\0';
    strftime(tbuf, sizeof(tbuf), "%b %d %H:%M", localtime(&st.st_mtime));
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    printf("%s %2ld %-8s %-8s %6ld %s %s\n", perm, (long)st.st_nlink,
           pw ? pw->pw_name : "?", gr ? gr->gr_name : "?", (long)st.st_size, tbuf, name);
}

int main(int argc, char *argv[])
{
    int longFmt = 0, i, count = 0;
    const char *dir = ".";
    char *names[500];
    DIR *dp;
    struct dirent *e;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) longFmt = 1;
        else dir = argv[i];
    }

    dp = opendir(dir);
    if (dp == NULL) { perror("ls"); return 1; }
    while ((e = readdir(dp)) != NULL)
        if (e->d_name[0] != '.')
            names[count++] = strdup(e->d_name);
    closedir(dp);

    qsort(names, count, sizeof(char *), cmp);
    for (i = 0; i < count; i++) {
        if (longFmt) printLong(dir, names[i]);
        else printf("%s  ", names[i]);
    }
    if (!longFmt) printf("\n");
    return 0;
}
