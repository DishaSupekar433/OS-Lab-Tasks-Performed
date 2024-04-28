#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 3
#define NUM_ITEMS 6 // Number of items to produce/consume

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int buffer_full = 0;
int buffer_empty = BUFFER_SIZE;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int item = 1;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item++;
        printf("Produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        buffer_full++;
        buffer_empty--;

        if (buffer_full == BUFFER_SIZE)
        {
            printf("Buffer is FULL!\n");
        }

        pthread_mutex_unlock(&mutex);
        // Signal that a slot has been filled
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        // Wait for a filled slot in the buffer
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        buffer_full--;
        buffer_empty++;

        if (buffer_empty == BUFFER_SIZE)
        {
            printf("Buffer is EMPTY!\n");
        }

        pthread_mutex_unlock(&mutex);
        // Signal that a slot has been emptied
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}