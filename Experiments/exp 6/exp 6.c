/* Exp 6: Preemptive priority scheduling (lower number = higher priority) */
#include <stdio.h>

int main()
{
    int n, i, at[20], bt[20], rt[20], pr[20], ct[20];
    int time = 0, done = 0, cur, best;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    printf("\nGantt chart (time : process)\n");
    while (done < n) {
        cur = -1; best = 9999;
        for (i = 0; i < n; i++)                  /* highest priority arrived process */
            if (at[i] <= time && rt[i] > 0 && pr[i] < best) {
                best = pr[i];
                cur = i;
            }
        if (cur == -1) {                         /* CPU idle */
            time++;
            continue;
        }
        printf("%d-%d : P%d\n", time, time + 1, cur + 1);
        rt[cur]--;                               /* run for one time unit */
        time++;
        if (rt[cur] == 0) {
            ct[cur] = time;
            done++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        avg_wt += wt;
        avg_tat += tat;
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat, wt);
    }
    printf("\nAverage Waiting Time    = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
