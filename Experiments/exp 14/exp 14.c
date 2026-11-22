/* Exp 14: File organisation using a single level directory */
#include <stdio.h>
#include <string.h>

#define MAX 20

struct Directory {
    char name[MAX][30];
    int count;
} dir;

int search(char *f)
{
    for (int i = 0; i < dir.count; i++)
        if (strcmp(dir.name[i], f) == 0) return i;
    return -1;
}

int main()
{
    int ch, i, pos;
    char f[30];

    dir.count = 0;
    do {
        printf("\n1. Create File\n2. Delete File\n3. Search File\n4. Display Files\n5. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the name of the file: ");
                scanf("%s", f);
                if (search(f) != -1) printf("File %s already exists\n", f);
                else if (dir.count == MAX) printf("Directory is full\n");
                else { strcpy(dir.name[dir.count++], f); printf("File %s created\n", f); }
                break;
            case 2:
                printf("Enter the name of the file to delete: ");
                scanf("%s", f);
                pos = search(f);
                if (pos == -1) printf("File %s not found\n", f);
                else {
                    strcpy(dir.name[pos], dir.name[--dir.count]);
                    printf("File %s deleted\n", f);
                }
                break;
            case 3:
                printf("Enter the name of the file to search: ");
                scanf("%s", f);
                if (search(f) == -1) printf("File %s not found\n", f);
                else printf("File %s is present in the directory\n", f);
                break;
            case 4:
                if (dir.count == 0) printf("Directory is empty\n");
                else {
                    printf("Files in the directory:\n");
                    for (i = 0; i < dir.count; i++) printf("  %s\n", dir.name[i]);
                }
                break;
            case 5: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 5);
    return 0;
}
