#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include<unistd.h>   
#include "server/socketManager.h"
#include "thread/threadManager.h"
#include "list/list.h"
#include "logs/log.h"
#include "config/configManager.h"


/*define*/
#define RETURN_ERROR -1
#define MAX_CLIENT 30

/*TODO add errno error */


/*Usage: ip port & conf path*/
int main(int argc, char** argv)
{
	/*variables*/
	int port;
	int listener_sock;	
	int c;
	char *welcomeMessage = "[SIMEON] : Welcome! I am the version 1.0\r\n";
	Client client_sock[MAX_CLIENT]; 
	int nb_client = 0;   
	struct sockaddr_in *client;
	char *msg;
	Config conf;
	LogLevel logLevel = initLoggerLevel();
	/*List list_clients = createList();*/


	plog("========================================================\n", logLevel.INFO);	
	plog("Simeon v1.0 start...\n", logLevel.INFO);	
	plog("========================================================\n", logLevel.INFO);	

	/*load the configuration*/
	plog("Load config\n", logLevel.INFO);
	conf = loadConfig();
	showConfig(conf);

	/*TODO format parameters*/
	argv = NULL;
	
	/*check parameters*/
	if (argc != 2 && argv == NULL)
	{
		/*init parameters with default values*/
		port = conf.DEFAULT_PORT;
	}

	
	/*create thread which wait for admin connection*/
	plog("Create listener for ADMIN connection...\n", logLevel.INFO);
	createThreadWichListenAdmin((void*)conf.CONTROL_PORT); 
	


	plog("Create listener for CLIENTS connection...\n", logLevel.INFO);
	listener_sock = createPassiveSocket(port);
	     
	while (1)
	{
		/*Accept an incoming connection*/
		plog("Waiting for connections...\n", logLevel.INFO);
		c = sizeof(struct sockaddr_in);

		/*create struct client and wait an incomming connection*/
		client = addSockaddr_in();  
		client_sock[nb_client].id = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);


		/*TODO init client with log system*/
		client_sock[nb_client].name = calloc(9, sizeof(char));
				

		/*TODO check if the client is already connected*/
		
		if (client_sock[nb_client].id < 0)
		{
			plog("accept failed from client\n", logLevel.ERROR);
			return RETURN_ERROR;
		}
		
		/*add to list of client
		list_clients = addElement(list_clients, &client_sock[nb_client]);
		showList(list_clients, printClient);*/

		/*format message to send to the new client*/
		msg= calloc(64, sizeof(char));
		sprintf(msg, "Connection accepted and moved in a thread, socket = %d\n", client_sock[nb_client].id);
		plog(msg, logLevel.INFO);
		

		/*write welcome*/  		
		write((int)client_sock[nb_client].id , welcomeMessage , strlen(welcomeMessage)); 
		memset(msg, 0, 64);
		sprintf(msg, "[SIMEON] : You are %d\n",client_sock[nb_client].id);
		write((int)client_sock[nb_client].id , msg , strlen(msg)); 
		free(msg);

		createThreadForAclient(&client_sock[nb_client]); /*create thread*/
		nb_client ++;
	}	
	



    return 0;
}





