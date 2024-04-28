#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100
#define MAX_FRAME_SIZE 10

int pageFrames[MAX_FRAME_SIZE];
int pageUsage[MAX_FRAME_SIZE];
int pageQueue[MAX_FRAME_SIZE];
int pageFaultsFIFO = 0;
int pageFaultsLFU = 0;
int pageFaultsLRU = 0;
int frameSize;

void initialize()
{
    for (int i = 0; i < MAX_FRAME_SIZE; i++)
    {
        pageFrames[i] = -1;
        pageUsage[i] = 0;
        pageQueue[i] = 0;
    }
}

void FIFO(int referenceString[], int size)
{
    initialize();
    int currentIndex = 0;

    for (int i = 0; i < size; i++)
    {
        int currentPage = referenceString[i];
        int pageFound = 0;

        for (int j = 0; j < frameSize; j++)
        {
            if (pageFrames[j] == currentPage)
            {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound)
        {
            pageFrames[currentIndex] = currentPage;
            currentIndex = (currentIndex + 1) % frameSize;
            pageFaultsFIFO++;
        }
    }
}

void LFU(int referenceString[], int size)
{
    initialize();

    for (int i = 0; i < size; i++)
    {
        int currentPage = referenceString[i];
        int pageFound = 0;

        for (int j = 0; j < frameSize; j++)
        {
            if (pageFrames[j] == currentPage)
            {
                pageFound = 1;
                pageUsage[j]++;
                break;
            }
        }

        if (!pageFound)
        {
            int minUsage = pageUsage[0];
            int minIndex = 0;

            for (int j = 1; j < frameSize; j++)
            {
                if (pageUsage[j] < minUsage)
                {
                    minUsage = pageUsage[j];
                    minIndex = j;
                }
            }

            pageFrames[minIndex] = currentPage;
            pageUsage[minIndex] = 1;
            pageFaultsLFU++;
        }
    }
}

void LRU(int referenceString[], int size)
{
    initialize();

    for (int i = 0; i < size; i++)
    {
        int currentPage = referenceString[i];
        int pageFound = 0;

        for (int j = 0; j < frameSize; j++)
        {
            if (pageFrames[j] == currentPage)
            {
                pageFound = 1;

                for (int k = j; k > 0; k--)
                {
                    pageFrames[k] = pageFrames[k - 1];
                }
                pageFrames[0] = currentPage;

                break;
            }
        }

        if (!pageFound)
        {
            for (int j = frameSize - 1; j > 0; j--)
            {
                pageFrames[j] = pageFrames[j - 1];
            }
            pageFrames[0] = currentPage;

            pageFaultsLRU++;
        }
    }
}

int main()
{
    int referenceString[MAX_PAGES];
    int size;

    printf("Enter the number of pages: ");
    scanf("%d", &size);

    if (size <= 0 || size > MAX_PAGES)
    {
        printf("Invalid number of pages. Please enter a value between 1 and %d.\n", MAX_PAGES);
        return 1;
    }

    printf("Enter the page reference string: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    if (frameSize <= 0 || frameSize > MAX_FRAME_SIZE)
    {
        printf("Invalid frame size. Please enter a value between 1 and %d.\n", MAX_FRAME_SIZE);
        return 1;
    }

    FIFO(referenceString, size);
    LFU(referenceString, size);
    LRU(referenceString, size);

    printf("Page Faults (FIFO): %d\n", pageFaultsFIFO);
    printf("Page Faults (LFU): %d\n", pageFaultsLFU);
    printf("Page Faults (LRU): %d\n", pageFaultsLRU);

    return 0;
}
