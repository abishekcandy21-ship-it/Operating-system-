/* Exp 7: Non-preemptive Shortest Job First (with arrival times) */
#include <stdio.h>

int main()
{
    int n, i, at[20], bt[20], ct[20], done[20] = {0};
    int time = 0, completed = 0, sel, min;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    while (completed < n) {
        sel = -1; min = 9999;
        for (i = 0; i < n; i++)                  /* shortest job among arrived ones */
            if (!done[i] && at[i] <= time && bt[i] < min) {
                min = bt[i];
                sel = i;
            }
        if (sel == -1) {                         /* nothing has arrived yet */
            time++;
            continue;
        }
        time += bt[sel];
        ct[sel] = time;
        done[sel] = 1;
        completed++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        avg_wt += wt;
        avg_tat += tat;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat, wt);
    }
    printf("\nAverage Waiting Time    = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
