/* Exp 15: File organisation using a two level directory
   (a master directory holding one directory per user) */
#include <stdio.h>
#include <string.h>

#define MAXU 10
#define MAXF 10

struct UserDir {
    char uname[30];
    char files[MAXF][30];
    int fcount;
} mfd[MAXU];                                     /* master file directory */
int ucount = 0;

int findUser(char *u)
{
    for (int i = 0; i < ucount; i++)
        if (strcmp(mfd[i].uname, u) == 0) return i;
    return -1;
}

int findFile(int u, char *f)
{
    for (int i = 0; i < mfd[u].fcount; i++)
        if (strcmp(mfd[u].files[i], f) == 0) return i;
    return -1;
}

int main()
{
    int ch, u, p, i, j;
    char user[30], f[30];

    do {
        printf("\n1. Create User Directory\n2. Create File\n3. Delete File\n4. Search File\n5. Display All\n6. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter user directory name: ");
                scanf("%s", user);
                if (findUser(user) != -1) printf("Directory %s already exists\n", user);
                else if (ucount == MAXU) printf("Master directory is full\n");
                else {
                    strcpy(mfd[ucount].uname, user);
                    mfd[ucount++].fcount = 0;
                    printf("Directory %s created\n", user);
                }
                break;
            case 2:
                printf("Enter user directory name and file name: ");
                scanf("%s %s", user, f);
                u = findUser(user);
                if (u == -1) printf("Directory %s not found\n", user);
                else if (findFile(u, f) != -1) printf("File %s already exists in %s\n", f, user);
                else if (mfd[u].fcount == MAXF) printf("Directory %s is full\n", user);
                else {
                    strcpy(mfd[u].files[mfd[u].fcount++], f);
                    printf("File %s created in %s\n", f, user);
                }
                break;
            case 3:
                printf("Enter user directory name and file name: ");
                scanf("%s %s", user, f);
                u = findUser(user);
                if (u == -1) { printf("Directory %s not found\n", user); break; }
                p = findFile(u, f);
                if (p == -1) printf("File %s not found in %s\n", f, user);
                else {
                    strcpy(mfd[u].files[p], mfd[u].files[--mfd[u].fcount]);
                    printf("File %s deleted from %s\n", f, user);
                }
                break;
            case 4:
                printf("Enter user directory name and file name: ");
                scanf("%s %s", user, f);
                u = findUser(user);
                if (u == -1) printf("Directory %s not found\n", user);
                else if (findFile(u, f) == -1) printf("File %s not found in %s\n", f, user);
                else printf("File %s found in %s\n", f, user);
                break;
            case 5:
                printf("\nMaster Directory structure:\n");
                for (i = 0; i < ucount; i++) {
                    printf("  %s/\n", mfd[i].uname);
                    for (j = 0; j < mfd[i].fcount; j++) printf("      %s\n", mfd[i].files[j]);
                }
                break;
            case 6: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 6);
    return 0;
}
