/* Exp 17: Deadlock avoidance - Banker's algorithm */
#include <stdio.h>

#define MAXP 10
#define MAXR 10

int n, m;
int alloc[MAXP][MAXR], max[MAXP][MAXR], need[MAXP][MAXR], avail[MAXR];

/* Safety algorithm: returns 1 if a safe sequence exists */
int isSafe(int print)
{
    int work[MAXR], finish[MAXP] = {0}, seq[MAXP], count = 0, i, j;

    for (j = 0; j < m; j++) work[j] = avail[j];

    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j]) break;
                if (j == m) {                    /* process i can finish */
                    for (j = 0; j < m; j++) work[j] += alloc[i][j];
                    finish[i] = 1;
                    seq[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) return 0;                    /* no process can proceed: unsafe */
    }
    if (print) {
        printf("Safe sequence: ");
        for (i = 0; i < n; i++) printf("P%d%s", seq[i], i < n - 1 ? " -> " : "\n");
    }
    return 1;
}

int main()
{
    int i, j, p, req[MAXR];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    printf("Enter the Allocation matrix:\n");
    for (i = 0; i < n; i++) for (j = 0; j < m; j++) scanf("%d", &alloc[i][j]);
    printf("Enter the Max matrix:\n");
    for (i = 0; i < n; i++) for (j = 0; j < m; j++) scanf("%d", &max[i][j]);
    printf("Enter the Available resources:\n");
    for (j = 0; j < m; j++) scanf("%d", &avail[j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nChecking the initial state...\n");
    if (isSafe(1)) printf("The system is in a SAFE state.\n");
    else { printf("The system is in an UNSAFE state (deadlock possible).\n"); return 0; }

    printf("\nEnter process number making a request: ");
    scanf("%d", &p);
    printf("Enter the request vector: ");
    for (j = 0; j < m; j++) scanf("%d", &req[j]);

    for (j = 0; j < m; j++) {
        if (req[j] > need[p][j]) {
            printf("Error: process has exceeded its maximum claim.\n");
            return 0;
        }
    }
    for (j = 0; j < m; j++) {
        if (req[j] > avail[j]) {
            printf("Resources not available. P%d must wait.\n", p);
            return 0;
        }
    }

    /* pretend to allocate */
    for (j = 0; j < m; j++) {
        avail[j] -= req[j]; alloc[p][j] += req[j]; need[p][j] -= req[j];
    }
    if (isSafe(1)) printf("Request can be granted immediately.\n");
    else {
        for (j = 0; j < m; j++) {                /* roll back */
            avail[j] += req[j]; alloc[p][j] -= req[j]; need[p][j] += req[j];
        }
        printf("Request cannot be granted: the system would enter an unsafe state.\n");
    }
    return 0;
}
