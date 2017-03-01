#include <pthread.h>

/*create and run a thread which is going to wait a connection on the admin port*/
pthread_t createThreadWichListenAdmin(void* arg);

/*create and run a thread which is going to communicate with a client*/
pthread_t createThreadForAclient(void* arg);
