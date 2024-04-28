#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 1000
#define MAX_PARTITIONS 50

typedef struct
{
    int size;
    int allocated;
} Partition;

Partition memory[MAX_PARTITIONS];
int num_partitions;

void initializeMemory()
{
    for (int i = 0; i < MAX_PARTITIONS; i++)
    {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

void displayMemory()
{
    printf("Memory Layout:\n");
    for (int i = 0; i < num_partitions; i++)
    {
        if (memory[i].allocated)
        {
            printf("[%d] Allocated (Size: %d)  ", i, memory[i].size);
        }
        else
        {
            printf("[%d] Free (Size: %d)  ", i, memory[i].size);
        }
    }
    printf("\n");
}

void firstFit(int processSize)
{
    for (int i = 0; i < num_partitions; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = 1;
            printf("First Fit: Allocated %d KB to process.\n", processSize);
            return;
        }
    }
    printf("First Fit: No suitable partition found for %d KB process.\n", processSize);
}

void bestFit(int processSize)
{
    int bestFitIndex = -1;
    int bestFitSize = MAX_MEMORY_SIZE + 1;

    for (int i = 0; i < num_partitions; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size < bestFitSize)
            {
                bestFitIndex = i;
                bestFitSize = memory[i].size;
            }
        }
    }

    if (bestFitIndex != -1)
    {
        memory[bestFitIndex].allocated = 1;
        printf("Best Fit: Allocated %d KB to process.\n", processSize);
    }
    else
    {
        printf("Best Fit: No suitable partition found for %d KB process.\n", processSize);
    }
}

void nextFit(int processSize, int *currentIndex)
{
    for (int i = *currentIndex; i < num_partitions; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = 1;
            *currentIndex = i;
            printf("Next Fit: Allocated %d KB to process.\n", processSize);
            return;
        }
    }

    for (int i = 0; i < *currentIndex; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = 1;
            *currentIndex = i;
            printf("Next Fit: Allocated %d KB to process.\n", processSize);
            return;
        }
    }

    printf("Next Fit: No suitable partition found for %d KB process.\n", processSize);
}

void worstFit(int processSize)
{
    int worstFitIndex = -1;
    int worstFitSize = -1;

    for (int i = 0; i < num_partitions; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size > worstFitSize)
            {
                worstFitIndex = i;
                worstFitSize = memory[i].size;
            }
        }
    }

    if (worstFitIndex != -1)
    {
        memory[worstFitIndex].allocated = 1;
        printf("Worst Fit: Allocated %d KB to process.\n", processSize);
    }
    else
    {
        printf("Worst Fit: No suitable partition found for %d KB process.\n", processSize);
    }
}

int main()
{
    int totalMemorySize, num_processes;
    int currentIndex = 0;

    printf("Enter total memory size (in KB): ");
    scanf("%d", &totalMemorySize);

    printf("Enter number of memory partitions: ");
    scanf("%d", &num_partitions);

    if (num_partitions <= 0 || num_partitions > MAX_PARTITIONS)
    {
        printf("Invalid number of partitions. Please enter a value between 1 and %d.\n", MAX_PARTITIONS);
        return 1;
    }

    for (int i = 0; i < num_partitions; i++)
    {
        printf("Enter size of partition %d (in KB): ", i);
        scanf("%d", &memory[i].size);
        memory[i].allocated = 0;
    }

    int choice;
    do
    {
        printf("\n1. First Fit  2. Best Fit  3. Next Fit  4. Worst Fit  5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int processSize;
        switch (choice)
        {
        case 1:
            printf("Enter size of process (in KB): ");
            scanf("%d", &processSize);
            firstFit(processSize);
            displayMemory();
            break;
        case 2:
            printf("Enter size of process (in KB): ");
            scanf("%d", &processSize);
            bestFit(processSize);
            displayMemory();
            break;
        case 3:
            printf("Enter size of process (in KB): ");
            scanf("%d", &processSize);
            nextFit(processSize, &currentIndex);
            displayMemory();
            break;
        case 4:
            printf("Enter size of process (in KB): ");
            scanf("%d", &processSize);
            worstFit(processSize);
            displayMemory();
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
    } while (choice != 5);

    return 0;
}
