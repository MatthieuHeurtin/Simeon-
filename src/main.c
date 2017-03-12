#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include<unistd.h>   
#include "server/socketManager.h"
#include "thread/threadManager.h"
#include "logs/log.h"
#include "signal_handler/handler.h"
#include "global_context/global_variables.h"
#include <errno.h>
#include <pthread.h>

/*define*/
#define RETURN_ERROR -1
#define MAX_CLIENT 30
#define MAX_THREAD 10

/*Usage: ip port & conf path*/
int main(int argc, char** argv)
{
	/*important variables*/
	Client client_sock[MAX_CLIENT];
	pthread_t threads[MAX_THREAD];

	/*global_context*/
	Context context = calloc(1, sizeof(Context));

	/*variables*/
	int id_of_incomming_connection;
	int port;
	int listener_sock;	
	int c;
	char *welcomeMessage = "[SIMEON] : Welcome! I am the version 1.0\r\n";
	struct sockaddr_in *sockaddr_client;
	char *msg;
	LogLevel logLevel = initLoggerLevel();
	Client incomming_client;
	
	/*init global context*/
	plog("[main.c] Init Global context\n", logLevel.INFO);
	/*load the configuration*/
	plog("[main.c] Load config\n", logLevel.INFO);
	context->conf = loadConfig();
	showConfig(context->conf);
	/*init list of connected clients*/	
	plog("[main.c] Init list of incomming connections\n", logLevel.INFO);
	context->connected_clients = createList();
	context->adminThread_event =1;

	/*catch signals
	handle_signal();
*/
	

	plog("========================================================\n", logLevel.INFO);	
	plog("Simeon v1.0 start...\n", logLevel.INFO);	
	plog("========================================================\n", logLevel.INFO);	


	


	/*TODO format parameters*/
	argv = NULL;
	
	/*check parameters*/
	if (argc != 2 && argv == NULL)
	{
		/*init parameters with default values*/
		port = context->conf.DEFAULT_PORT;
	}

	
	/*create thread which wait for admin connection*/
	plog("Create listener for ADMIN connection...\n", logLevel.INFO);
	threads[0] = createThreadWichListenAdmin((void*)context); 
		


	plog("Create listener for CLIENTS connection...\n", logLevel.INFO);
	listener_sock = createPassiveSocket(port);
	     
	while (1)
	{
fprintf(stdout, "MATTTTTT %d\n", context->adminThread_event);
		/*Accept an incoming connection*/
		plog("Waiting for connections...\n", logLevel.INFO);
		

		/*create struct client and wait an incomming connection*/
		c = sizeof(struct sockaddr_in);
		sockaddr_client = addSockaddr_in();  
		id_of_incomming_connection = accept(listener_sock, (struct sockaddr *)sockaddr_client, (socklen_t*)&c);

		if (id_of_incomming_connection < 0)
		{
			plog("[main.c] accept failed from client\n", logLevel.ERROR);
		}
		
		incomming_client.id = id_of_incomming_connection;
		/*TODO init client with log system*/
		incomming_client.name = calloc(64, sizeof(char));
		strcpy(incomming_client.name, context->conf.DEFAULT_NAME);		
		context->connected_clients = addElement(context->connected_clients, &incomming_client); 
		
		/*TODO check if the client is already connected*/
		
	
		/*add to list of client
		list_clients = addElement(list_clients, &client_sock[nb_client]);
		showList(list_clients, printClient);*/

		/*format message to send to the new client*/
		msg= calloc(64, sizeof(char));
		sprintf(msg, "Connection accepted and moved in a thread, socket = %d\n", incomming_client.id);
		plog(msg, logLevel.INFO);
		

		/*write welcome*/  		
		write((int)incomming_client.id , welcomeMessage , strlen(welcomeMessage)); 
		memset(msg, 0, 64);
		sprintf(msg, "[SIMEON] : You are %d\n",incomming_client.id);
		write((int)incomming_client.id , msg , strlen(msg)); 
		free(msg);

		createThreadForAclient((void*)context); /*create thread*/
		context->nb_client ++;
	}	
    return 0;
}





