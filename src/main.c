#include<stdlib.h>
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

//usage ip port
int main(int argc, char** argv)
{
	//variables
	int port;
	char *ip_addr; 
	int listener_sock; 
	int client_sock;
	int c;
	int read_size;
    

	struct sockaddr_in client;
	



	//check parameters
	if (argc != 2)
	{
		//init parameters with default values
		port = 8888;
		ip_addr = calloc(9, sizeof(char));		
		strcpy(ip_addr, "127.0.0.1");
	}


	//create server address
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_aton(ip_addr, &server.sin_addr);

  char client_message[2000];
     
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
        fprintf(stdout,"bind failed. Error\n");
        return 1;
    }
    fprintf(stdout,"bind done\n");
     
    //sokcet is passive
    listen(listener_sock , 2);
     
    //Accept and incoming connection
    fprintf(stdout,"Waiting for incoming connections...\n");
//    c = sizeof(struct sockaddr_in);

    //wait an incoming client
    client_sock = accept(listener_sock, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    fprintf(stdout,"Connection accepted\n");
     
createAddr();


//=============================================beow don't change



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
     
    return 0;
}
