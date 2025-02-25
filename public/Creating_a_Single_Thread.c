#include <stdio.h>
#include <pthread.h>

void *print_message()
{
    printf("Hello from thread!\n");
    return NULL;
}

int main ()
{
	pthread_t thread_id; // Declare a thread

	pthread_create(&thread_id , NULL, print_message, NULL); // creat thread
	pthread_join(thread_id, NULL); // Wait for the thread to finish
	return 0;
}