#include<sys/socket.h>
#include<arpa/inet.h> /*inet_addr*/
#include <stdlib.h>
#include <netinet/in.h>
#include "../logs/log.h"

#define RETURN_ERROR -1

/*configure an ip_address*/
void createAddr(struct sockaddr_in* server ,int port)
{
	(*server).sin_family = AF_INET;
	(*server).sin_port = htons(port);
	server->sin_addr.s_addr = htonl(INADDR_ANY);
}


/*create a new sockaddr client*/
struct sockaddr_in *addSockaddr_in()
{
	struct sockaddr_in *newSockaddr_in = (struct sockaddr_in *)calloc(1 ,sizeof(struct sockaddr_in));
	return newSockaddr_in;

}

/*Create a passive socket*/
int createPassiveSocket(int port)
{
	struct sockaddr_in server;
	int listener_sock;
	LogLevel logLevel = initLoggerLevel();
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

	return listener_sock;
}
