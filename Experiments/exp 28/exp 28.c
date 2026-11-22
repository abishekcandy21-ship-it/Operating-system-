/* Exp 28: Simulation of the UNIX 'grep' command
   Usage: ./a.out pattern filename */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char line[1024];
    int lineno = 0, matches = 0;

    if (argc != 3) {
        printf("Usage: %s pattern filename\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[2], "r");
    if (fp == NULL) { perror("grep"); return 1; }

    while (fgets(line, sizeof(line), fp) != NULL) {
        lineno++;
        if (strstr(line, argv[1]) != NULL) {     /* line contains the pattern */
            printf("%d: %s", lineno, line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
            matches++;
        }
    }
    fclose(fp);
    printf("\n%d matching line(s) found for \"%s\" in %s\n", matches, argv[1], argv[2]);
    return 0;
}
