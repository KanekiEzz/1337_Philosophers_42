#include <stdio.h>
#include <pthread.h>

void *print_message(void *args)
{
    int num = *(int *)args; // Convert argument to integer
    printf("Thread %d is runnig\n", num);
    return  NULL;
}

int main ()
{
    pthread_t threads[3];   // Declare an array for 3 threads
    int args[3] = {1, 2, 3};    // Arguments for each thread

    int i = 0;
    while (i < 3)
    {
        pthread_create(&threads[i], NULL, print_message, &args[i]);
        i++;
    }

    i = 0;
    while (i < 3)
        pthread_join(threads[i++] ,NULL);   // Wait for each thread to finish

    return 0;
}