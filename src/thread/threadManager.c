
#include <pthread.h>

#include "threadMethod.h"


#include<stdlib.h>
#include<stdio.h>
void createThread()
{
fprintf(stdout, "I am creating a thread\n");
pthread_t inc_x_thread;
pthread_create(&inc_x_thread, NULL, threadMethod, NULL) ;
}



