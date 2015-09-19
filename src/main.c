#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include<unistd.h>   

#include "server/socketManager.h"
#include "thread/threadManager.h"
#include "thread/threadMethod.h"
#include "list/list.h"

//define
#define RETURN_ERROR -1
#define DEFAULT_PORT 8888
#define MAX_CLIENT 30



//Usage: ip port
int main(int argc, char** argv)
{

	//variables
	int port;
	char *ip_addr; 
	int listener_sock; 
	int c;
	char *welcomeMessage = "Welcome on Simeon v1.0\r\n";
	Client client_sock[MAX_CLIENT]; 
	int nb_client = 0;   
	List list_clients = createList();

	//TODO format parameters

	//check parameters
	if (argc != 2)
	{
		//init parameters with default values
		port = DEFAULT_PORT;
		ip_addr = calloc(9, sizeof(char));		
		strcpy(ip_addr, "127.0.0.1");
	}

	//create server address
	struct sockaddr_in server;
	createAddr(&server, port, ip_addr);
     
	//Create socket
	listener_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (listener_sock == -1)
	{
		fprintf(stderr, "Could not create Listener_sock");
		return RETURN_ERROR;
	}
	fprintf(stdout, "Listener_sock created\n");
     
	//put some options
	int opt = 1;
	if( setsockopt(listener_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
	{
		fprintf(stderr,"setsockopt failed");
		return RETURN_ERROR;
	}
     
	//Bind
	if( bind(listener_sock,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		fprintf(stderr,"bind failed. Error\n");
		return RETURN_ERROR;
	}
	fprintf(stdout,"bind done\n");
	     
	//sokcet is passive
	listen(listener_sock , 2);
	     


	while (1)
	{
		//Accept and incoming connection
		fprintf(stdout,"Waiting for incoming connections...\n");
		c = sizeof(struct sockaddr_in);
		struct sockaddr_in *client = addSockaddr_in();  
	
		//wait an incoming client
		client_sock[nb_client].id = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);
	
				

		//TODO check if the client is already connected
		
		if (client_sock[nb_client].id < 0)
		{
			fprintf(stderr,"accept failed from client\n");
			return RETURN_ERROR;
		}
		
		//add to list of client
		list_clients = addElement(list_clients, &client_sock[nb_client]);
		fprintf(stdout, "Print client\n");
		showList(list_clients, printClient);


		fprintf(stdout,"Connection accepted and moved in a thread, socket = %d\n", client_sock[nb_client].id);
		write((int)client_sock[nb_client].id , welcomeMessage , strlen(welcomeMessage)); //write welcome
		createThread(connectionEtablished, &client_sock[nb_client]); //create thread
		nb_client ++;
	}	
	


	
//=============================================below don't change

/*


    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     */
    return 0;
}





