#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include<unistd.h>   

#include "server/socketManager.h"
#include "thread/threadManager.h"
#include "thread/threadMethod.h"
#include "list/list.h"

/*define*/
#define RETURN_ERROR -1
#define DEFAULT_PORT 8888
#define MAX_CLIENT 30



/*Usage: ip port*/
int main(int argc, char** argv)
{


	/*variables*/
	int port;
	char *ip_addr; 
	int listener_sock; 
	int c;
	char *welcomeMessage = "[SIMEON] : Welcome! I am the version 1.0\r\n";
	Client client_sock[MAX_CLIENT]; 
	int nb_client = 0;   
	List list_clients = createList();
	struct sockaddr_in server;
	int opt = 1;
	struct sockaddr_in *client;

	/*TODO format parameters*/
	argv = NULL;
	
	/*check parameters*/
	if (argc != 2 && argv == NULL)
	{
		/*init parameters with default values*/
		port = DEFAULT_PORT;
		ip_addr = calloc(9, sizeof(char));		
		strcpy(ip_addr, "127.0.0.1");
	}

	/*create server address*/
	createAddr(&server, port, ip_addr);
     
	/*Create socket*/
	listener_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (listener_sock == -1)
	{
		fprintf(stderr, "Could not create Listener_sock");
		return RETURN_ERROR;
	}
	fprintf(stdout, "Listener_sock created\n");
     
	/*put some options*/
	if( setsockopt(listener_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
	{
		fprintf(stderr,"setsockopt failed");
		return RETURN_ERROR;
	}
     
	/*Bind*/
	if( bind(listener_sock,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		/*print the error message*/
		fprintf(stderr,"bind failed. Error\n");
		return RETURN_ERROR;
	}
	fprintf(stdout,"bind done\n");
	     
	/*sokcet is passive*/
	listen(listener_sock , 2);
	     


	while (1)
	{
		/*Accept and incoming connection*/
		fprintf(stdout,"Waiting for incoming connections...\n");
		c = sizeof(struct sockaddr_in);

		/*create struct client and wait an incomming connection*/
		client = addSockaddr_in();  
		client_sock[nb_client].id = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);
		/*TODO init client with log system*/
		client_sock[nb_client].name = calloc(9, sizeof(char));
				

		/*TODO check if the client is already connected*/
		
		if (client_sock[nb_client].id < 0)
		{
			fprintf(stderr,"accept failed from client\n");
			return RETURN_ERROR;
		}
		
		/*add to list of client*/
		list_clients = addElement(list_clients, &client_sock[nb_client]);
		/*showList(list_clients, printClient);*/


		fprintf(stdout,"Connection accepted and moved in a thread, socket = %d\n", client_sock[nb_client].id);
		write((int)client_sock[nb_client].id , welcomeMessage , strlen(welcomeMessage)); /*write welcome*/
		createThread(connectionEtablished, &client_sock[nb_client]); /*create thread*/
		nb_client ++;
	}	
	



    return 0;
}





