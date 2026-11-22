/* Exp 33: Optimal page replacement */
#include <stdio.h>

int main()
{
    int n, f, i, j, k, faults = 0, hit;
    int pages[50], frame[10];

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) frame[i] = -1;

    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++)
            if (frame[j] == pages[i]) { hit = 1; break; }
        if (!hit) {
            int victim = -1, farthest = -1;
            for (j = 0; j < f; j++)
                if (frame[j] == -1) { victim = j; break; }       /* free frame */
            if (victim == -1) {
                for (j = 0; j < f; j++) {                        /* page used farthest in future */
                    for (k = i + 1; k < n; k++)
                        if (frame[j] == pages[k]) break;
                    if (k > farthest) { farthest = k; victim = j; }
                }
            }
            frame[victim] = pages[i];
            faults++;
        }
        printf("%d\t", pages[i]);
        for (j = 0; j < f; j++) {
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("\t%s\n", hit ? "Hit" : "Page Fault");
    }
    printf("\nTotal page faults = %d\n", faults);
    printf("Total page hits   = %d\n", n - faults);
    return 0;
}
