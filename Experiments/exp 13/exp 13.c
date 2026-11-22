/* Exp 13: Memory allocation strategies - First Fit, Best Fit and Worst Fit */
#include <stdio.h>
#include <string.h>

#define MAX 20

void allocate(int nb, int np, int blocks[], int proc[], int strategy)
{
    int rem[MAX], alloc[MAX], i, j, idx;

    for (i = 0; i < nb; i++) rem[i] = blocks[i];
    for (i = 0; i < np; i++) alloc[i] = -1;

    for (i = 0; i < np; i++) {
        idx = -1;
        for (j = 0; j < nb; j++) {
            if (rem[j] >= proc[i]) {
                if (strategy == 1) { idx = j; break; }                      /* first fit */
                if (strategy == 2 && (idx == -1 || rem[j] < rem[idx])) idx = j;  /* best fit */
                if (strategy == 3 && (idx == -1 || rem[j] > rem[idx])) idx = j;  /* worst fit */
            }
        }
        if (idx != -1) {
            alloc[i] = idx;
            rem[idx] -= proc[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, proc[i]);
        if (alloc[i] != -1) printf("%d\n", alloc[i] + 1);
        else printf("Not Allocated\n");
    }
}

int main()
{
    int nb, np, i, ch, blocks[MAX], proc[MAX];

    printf("Enter the number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter the size of each block:\n");
    for (i = 0; i < nb; i++) scanf("%d", &blocks[i]);

    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter the size of each process:\n");
    for (i = 0; i < np; i++) scanf("%d", &proc[i]);

    do {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("\n--- First Fit ---");  allocate(nb, np, blocks, proc, 1); break;
            case 2: printf("\n--- Best Fit ---");   allocate(nb, np, blocks, proc, 2); break;
            case 3: printf("\n--- Worst Fit ---");  allocate(nb, np, blocks, proc, 3); break;
            case 4: break;
            default: printf("Invalid choice\n");
        }
    } while (ch != 4);
    return 0;
}
