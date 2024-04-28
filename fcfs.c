#include <stdio.h>

struct Process
{
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);

        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);

        processes[i].pid = i + 1;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            processes[i].waiting_time = 0;
        }
        else
        {
            int completion_time = processes[i - 1].turnaround_time + processes[i - 1].arrival_time;
            processes[i].waiting_time = (completion_time > processes[i].arrival_time) ? (completion_time - processes[i].arrival_time) : 0;
        }

        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    double average_waiting_time = (double)total_waiting_time / n;
    double average_turnaround_time = (double)total_turnaround_time / n;

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time,
               processes[i].arrival_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
