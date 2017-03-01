#include <pthread.h>
#include "threadMethods/admin.h"
#include "threadMethods/client.h"

/*the only arg is the port*/
pthread_t createThreadWichListenAdmin(void * arg)
{
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, listenAdmin, arg) ;
	return new_thread;
}



pthread_t createThreadForAclient(void* arg)
{
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, connectionEtablished, arg);
	return new_thread;
}





