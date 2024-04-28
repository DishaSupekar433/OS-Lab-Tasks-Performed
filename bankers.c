#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

void inputData()
{
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the maximum resources required by each process:\n");
    for (i = 0; i < num_processes; i++)
    {
        for (j = 0; j < num_resources; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocated resources for each process:\n");
    for (i = 0; i < num_processes; i++)
    {
        for (j = 0; j < num_resources; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("Enter the available resources: ");
    for (i = 0; i < num_resources; i++)
    {
        scanf("%d", &available[i]);
    }
}

int checkSafety()
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int i, j, k;

    for (i = 0; i < num_resources; i++)
    {
        work[i] = available[i];
    }

    for (i = 0; i < num_processes; i++)
    {
        finish[i] = 0;
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0;

    while (count < num_processes)
    {
        int found = 0;
        for (i = 0; i < num_processes; i++)
        {
            if (finish[i] == 0)
            {
                int canAllocate = 1;
                for (j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (k = 0; k < num_resources; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            // If no process can be allocated, the system is not in a safe state
            return 0;
        }
    }

    printf("Safe Sequence: ");
    for (i = 0; i < num_processes; i++)
    {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1; // System is in a safe state
}

int main()
{
    inputData();
    if (checkSafety())
    {
        printf("The system is in a safe state.\n");
    }
    else
    {
        printf("The system is not in a safe state.\n");
    }
    return 0;
}
