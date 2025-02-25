#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define NUM_PHILOS 200

typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;

pthread_mutex_t forks[NUM_PHILOS];
t_philo philos[NUM_PHILOS];

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    printf("Philosopher %d is thinking\n", philo->id);

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("Philosopher %d picked up left fork\n", philo->id);
        pthread_mutex_lock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        printf("Philosopher %d picked up right fork\n", philo->id);
        pthread_mutex_lock(philo->left_fork);
    }

    printf("Philosopher %d is eating 🍝\n", philo->id);
    usleep(1000 * 1000);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    printf("Philosopher %d put down forks and is thinking again\n", philo->id);

    return NULL;
}

int main()
{
    int i = 0;
    memset(forks, 0, sizeof(forks));
    while (i < NUM_PHILOS)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < NUM_PHILOS)
    {
        philos[i].id = i;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % NUM_PHILOS]; // Circular forks
        pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < NUM_PHILOS)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    i = 0;
    while (i < NUM_PHILOS)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    return 0;
}
