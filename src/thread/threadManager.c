
#include <pthread.h>

#include "threadMethod.h"
#include<stdlib.h>
#include<stdio.h>

void createThread( void *threadMethod, void* arg)
{
fprintf(stdout,"I am creating a thread\n");
pthread_t new_thread;
pthread_create(&new_thread, NULL, threadMethod, arg) ;
}



