#include <pthread.h>
#include "threadMethods/admin.h"
#include "threadMethods/client.h"

/*the only arg is the port*/
void createThreadWichListenAdmin(void * arg)
{
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, listenAdmin, arg) ;
}



void createThreadForAclient(void* arg)
{
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, connectionEtablished, arg) ;
}





