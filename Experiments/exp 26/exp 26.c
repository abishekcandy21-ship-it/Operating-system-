/* Exp 26: File management operations - create, write, read, append,
   rename and delete a file */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    char buffer[100];
    int ch;

    do {
        printf("\n1. Create/Write file\n2. Read file\n3. Append to file\n4. Rename file\n5. Delete file\n6. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                file = fopen("example.txt", "w");
                if (file == NULL) { printf("Error opening the file for writing.\n"); break; }
                fprintf(file, "Hello, World!\n");
                fprintf(file, "This is a C file management example.\n");
                fclose(file);
                printf("File 'example.txt' created and written.\n");
                break;
            case 2:
                file = fopen("example.txt", "r");
                if (file == NULL) { printf("File 'example.txt' does not exist.\n"); break; }
                printf("Contents of example.txt:\n");
                while (fgets(buffer, sizeof(buffer), file) != NULL)
                    printf("%s", buffer);
                fclose(file);
                break;
            case 3:
                file = fopen("example.txt", "a");
                if (file == NULL) { printf("Error opening the file for appending.\n"); break; }
                fprintf(file, "This line was appended.\n");
                fclose(file);
                printf("Line appended to 'example.txt'.\n");
                break;
            case 4:
                if (rename("example.txt", "renamed.txt") == 0)
                    printf("File renamed to 'renamed.txt'.\n");
                else
                    printf("Rename failed.\n");
                break;
            case 5:
                if (remove("renamed.txt") == 0)
                    printf("File 'renamed.txt' deleted.\n");
                else
                    printf("Delete failed (file not found).\n");
                break;
            case 6: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 6);
    return 0;
}
