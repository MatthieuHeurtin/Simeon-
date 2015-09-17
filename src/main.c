#include<stdlib.h>
#include<stdio.h>
#include<string.h>    //strlen
#include<unistd.h>    //write

#include "server/socketManager.h"
#include "thread/threadManager.h"

//define
#define RETURN_ERROR -1
#define DEFAULT_PORT 8888


//Usage: ip port
int main(int argc, char** argv)
{
	//variables
	int port;
	char *ip_addr; 
	int listener_sock; 
	int c;
	char client_message[2000];
    

	struct sockaddr_in client;
	

createThread();
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
		fprintf(stdout, "Could not create socket");
	}
	fprintf(stdout, "Socket created\n");
     

     
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
	     
	//Accept and incoming connection
	fprintf(stdout,"Waiting for incoming connections...\n");
	c = sizeof(struct sockaddr_in);

	//wait an incoming client
	int client_sock = accept(listener_sock, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		fprintf(stderr,"accept failed");
		return RETURN_ERROR;
	}
	fprintf(stdout,"Connection accepted\n");
	     



//=============================================beow don't change

/*

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
    }
     
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
