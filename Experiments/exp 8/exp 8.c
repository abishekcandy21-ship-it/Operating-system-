/* Exp 8: Round Robin scheduling */
#include <stdio.h>

int main()
{
    int n, i, q, at[20], bt[20], rt[20], ct[20];
    int queue[200], front = 0, rear = 0, inq[20] = {0};
    int time = 0, done = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter the time quantum: ");
    scanf("%d", &q);

    queue[rear++] = 0;                           /* assumes P1 arrives first (sorted by AT) */
    inq[0] = 1;
    time = at[0];

    printf("\nGantt chart (start-end : process)\n");
    while (done < n) {
        if (front == rear) {                     /* CPU idle: jump to next arrival */
            for (i = 0; i < n; i++)
                if (rt[i] > 0) { time = at[i]; queue[rear++] = i; inq[i] = 1; break; }
        }
        int p = queue[front++];
        int run = (rt[p] < q) ? rt[p] : q;
        printf("%d-%d : P%d\n", time, time + run, p + 1);
        time += run;
        rt[p] -= run;
        for (i = 0; i < n; i++)                  /* add newly arrived processes */
            if (!inq[i] && at[i] <= time && rt[i] > 0) {
                queue[rear++] = i;
                inq[i] = 1;
            }
        if (rt[p] > 0)
            queue[rear++] = p;                   /* not finished: back of the queue */
        else {
            ct[p] = time;
            done++;
        }
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
