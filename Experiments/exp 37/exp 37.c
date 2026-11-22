/* Exp 37: FCFS disk scheduling */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, head, req[50], seek, total = 0;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nOrder of service: %d", head);
    for (i = 0; i < n; i++) {
        seek = abs(req[i] - head);
        total += seek;
        head = req[i];
        printf(" -> %d", head);
    }
    printf("\n\nTotal head movement = %d cylinders\n", total);
    printf("Average seek length = %.2f\n", (float)total / n);
    return 0;
}
