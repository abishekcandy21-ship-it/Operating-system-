/* Exp 32: LRU (Least Recently Used) page replacement */
#include <stdio.h>

int main()
{
    int n, f, i, j, faults = 0, hit, time = 0;
    int pages[50], frame[10], last[10];

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) { frame[i] = -1; last[i] = -1; }

    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < n; i++) {
        hit = 0;
        time++;
        for (j = 0; j < f; j++)
            if (frame[j] == pages[i]) {
                hit = 1;
                last[j] = time;                  /* update last used time */
                break;
            }
        if (!hit) {
            int victim = 0;
            for (j = 0; j < f; j++) {            /* empty frame, else least recently used */
                if (frame[j] == -1) { victim = j; break; }
                if (last[j] < last[victim]) victim = j;
            }
            frame[victim] = pages[i];
            last[victim] = time;
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
