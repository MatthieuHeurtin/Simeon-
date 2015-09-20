#include <pthread.h>
#include "threadMethod.h"
#include<stdlib.h>
#include<stdio.h>

void createThread( void *(*threadMethod)  (void*), void* arg)
{
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, threadMethod, arg) ;
}



