/* Exp 39: C-SCAN disk scheduling - head moves towards the end of the disk,
   jumps to cylinder 0 and continues servicing in the same direction */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, t, head, size, req[50], total = 0, pos, cur;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size (number of cylinders): ");
    scanf("%d", &size);

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) { t = req[j]; req[j] = req[j + 1]; req[j + 1] = t; }

    for (pos = 0; pos < n && req[pos] < head; pos++);

    printf("\nOrder of service: %d", head);
    cur = head;
    for (i = pos; i < n; i++) {
        total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur);
    }
    total += (size - 1) - cur; cur = size - 1; printf(" -> %d", cur);   /* reach the end */
    total += size - 1; cur = 0; printf(" -> %d", cur);                  /* jump back to 0 */
    for (i = 0; i < pos; i++) {
        total += abs(req[i] - cur); cur = req[i]; printf(" -> %d", cur);
    }
    printf("\n\nTotal head movement = %d cylinders (including the return jump)\n", total);
    printf("Average seek length = %.2f\n", (float)total / n);
    return 0;
}
