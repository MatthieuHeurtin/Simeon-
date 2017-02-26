/*create and run a thread which is going to wait a connection on the admin port*/
void createThreadWichListenAdmin(void* arg);

/*create and run a thread which is going to communicate with a client*/
void createThreadForAclient(void* arg);
