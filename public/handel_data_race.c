#include <stdio.h>
#include <pthread.h>

int mails;
pthread_mutex_t mutex;

void *rout()
{
    int i = 0;
    while (i < 1000000)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main()
{
    pthread_t t[4];
    pthread_mutex_init(&mutex, NULL);
    int i = 0;
    while (i < 4)
    {
        pthread_create(&t[i++], NULL, &rout, NULL);
        printf("Thread %d has started\n", i);
    }
    i = 0;
    while (i < 4)
    {
        pthread_join(t[i++], NULL);
        printf("Thread %d has fineshed execution\n", i);
    }
    printf("Number of mails %d\n", mails);
    pthread_mutex_destroy(&mutex);

    return 0;
}