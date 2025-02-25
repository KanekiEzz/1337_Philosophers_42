#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
int counter = 0;

void *increment(void *arg)
{
    pthread_mutex_lock(&lock);
    counter++;
    printf("Counter: %d\n", counter);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t threads[5];

    pthread_mutex_init(&lock, NULL);
    int i = 0;
    while (i < 5)
    {
        pthread_create(&threads[i], NULL, increment, NULL);
        i++;
    }
    i = 0;
    while (i < 5)
        pthread_join(threads[i++], NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}