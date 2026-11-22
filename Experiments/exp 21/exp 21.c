/* Exp 21: Worst fit algorithm of memory management */
#include <stdio.h>

int main()
{
    int nb, np, i, j, idx, blocks[20], rem[20], proc[20], alloc[20];

    printf("Enter the number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter the size of each block:\n");
    for (i = 0; i < nb; i++) { scanf("%d", &blocks[i]); rem[i] = blocks[i]; }

    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter the size of each process:\n");
    for (i = 0; i < np; i++) { scanf("%d", &proc[i]); alloc[i] = -1; }

    for (i = 0; i < np; i++) {
        idx = -1;
        for (j = 0; j < nb; j++) {
            if (rem[j] >= proc[i]) {
                if (idx == -1 || rem[j] > rem[idx]) idx = j;   /* largest hole */
            }
        }
        if (idx != -1) {
            alloc[i] = idx;
            rem[idx] -= proc[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\tFragment left\n");
    for (i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, proc[i]);
        if (alloc[i] != -1)
            printf("%d\t\t%d\t\t%d\n", alloc[i] + 1, blocks[alloc[i]], rem[alloc[i]]);
        else
            printf("Not Allocated\n");
    }
    return 0;
}
