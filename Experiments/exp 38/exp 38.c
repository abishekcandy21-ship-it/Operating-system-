/* Exp 38: SCAN (elevator) disk scheduling - head moves towards the end of
   the disk (here: towards higher cylinders first), then reverses */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, t, head, size, req[50], total = 0, pos;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size (number of cylinders): ");
    scanf("%d", &size);

    for (i = 0; i < n - 1; i++)                  /* sort requests */
        for (j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) { t = req[j]; req[j] = req[j + 1]; req[j + 1] = t; }

    for (pos = 0; pos < n && req[pos] < head; pos++);   /* first request >= head */

    printf("\nOrder of service: %d", head);
    int cur = head;
    for (i = pos; i < n; i++) {                  /* move towards the end */
        total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur);
    }
    total += abs((size - 1) - cur); cur = size - 1;      /* go to the last cylinder */
    printf(" -> %d", cur);
    for (i = pos - 1; i >= 0; i--) {             /* reverse direction */
        total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur);
    }
    printf("\n\nTotal head movement = %d cylinders\n", total);
    printf("Average seek length = %.2f\n", (float)total / n);
    return 0;
}
