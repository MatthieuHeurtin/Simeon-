#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include<unistd.h>   
#include "server/socketManager.h"
#include "thread/threadManager.h"
#include "thread/threadMethod.h"
#include "list/list.h"
#include "logs/log.h"
#include "config/configManager.h"


/*define*/
#define RETURN_ERROR -1
#define MAX_CLIENT 30

/*TODO add errno error */


/*Usage: ip port*/
int main(int argc, char** argv)
{
	/*variables*/
	int port;
	int listener_sock;	
	int c;
	char *welcomeMessage = "[SIMEON] : Welcome! I am the version 1.0\r\n";
	Client client_sock[MAX_CLIENT]; 
	int nb_client = 0;   
	List list_clients = createList();
	struct sockaddr_in server;
	int opt = 1;
	struct sockaddr_in *client;
	char *msg;
	Config conf;
	LogLevel logLevel = initLoggerLevel();
	


	/*load the configuration*/
	plog("Simeon v1.0 start...\n", logLevel.INFO);	
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
	createThread(listenAdmin, NULL); 
	




	/*create server address*/
	createAddr(&server, port);
     
	/*Create socket*/
	listener_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (listener_sock == -1)
	{
		plog("Could not create Listener_sock", logLevel.ERROR);
		return RETURN_ERROR;
	}
	plog("Listener_sock created\n", logLevel.INFO);
     
	/*put some options*/
	if( setsockopt(listener_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
	{
		plog("setsockopt failed\n", logLevel.ERROR);
		return RETURN_ERROR;
	}
     
	/*Bind*/
	if( bind(listener_sock,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		/*print the error message*/
		plog("bind failed. Error\n", logLevel.ERROR);
		return RETURN_ERROR;
	}
	plog("Bind done\n", logLevel.INFO);
	     
	/*sokcet is passive*/
	listen(listener_sock , 2);
	     


	while (1)
	{
		/*Accept an incoming connection*/
		plog("Waiting for incoming connections...\n", logLevel.INFO);
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
		
		/*add to list of client*/
		list_clients = addElement(list_clients, &client_sock[nb_client]);
		/*showList(list_clients, printClient);*/

		msg= calloc(64, sizeof(char));
		sprintf(msg, "Connection accepted and moved in a thread, socket = %d\n", client_sock[nb_client].id);
		plog(msg, logLevel.INFO);
		free(msg);
		write((int)client_sock[nb_client].id , welcomeMessage , strlen(welcomeMessage)); /*write welcome*/
		createThread(connectionEtablished, &client_sock[nb_client]); /*create thread*/
		nb_client ++;
	}	
	



    return 0;
}





