#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t mutex;
sem_t forks[NUM_PHILOSOPHERS];
int state[NUM_PHILOSOPHERS];

void test(int philosopher)
{
    if (state[philosopher] == HUNGRY &&
        state[(philosopher + 4) % NUM_PHILOSOPHERS] != EATING &&
        state[(philosopher + 1) % NUM_PHILOSOPHERS] != EATING)
    {
        state[philosopher] = EATING;
        printf("Philosopher %d is eating\n", philosopher);
        sem_post(&forks[philosopher]);
    }
}

void grab_forks(int philosopher)
{
    sem_wait(&mutex);
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is hungry\n", philosopher);
    test(philosopher);
    sem_post(&mutex);
    sem_wait(&forks[philosopher]);
    sleep(1); // Simulate eating
}

void put_forks(int philosopher)
{
    sem_wait(&mutex);
    state[philosopher] = THINKING;
    printf("Philosopher %d is thinking\n", philosopher);
    test((philosopher + 4) % NUM_PHILOSOPHERS);
    test((philosopher + 1) % NUM_PHILOSOPHERS);
    sem_post(&mutex);
}

void *philosopher_thread(void *arg)
{
    int philosopher = *((int *)arg);
    while (1)
    {
        grab_forks(philosopher);
        put_forks(philosopher);
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philo_ids[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 0);
        state[i] = THINKING;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philo_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher_thread, &philo_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
