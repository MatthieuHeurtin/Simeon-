#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/types.h>
#include <sys/socket.h>
#include "../../logs/log.h"
#include "../..//server/socketManager.h"
#include "threadMethod.h"
/*All this method are executed by a thread. This thread represents a connection with the client*/
void *listenAdmin(void *port)
{
	int listener_sock;
	char *admin_message = NULL;
	char * msg =NULL;
	int c;
	int acceptedSocket;
	struct sockaddr_in *client;
	LogLevel logLevel = initLoggerLevel();
	
	admin_message = calloc(512, sizeof(char));

	 /*connect on this socket if you want to admin Simeon*/
	listener_sock = createPassiveSocket((int)port);

	

	while (1)
	{
		plog("[admin.c] Start listenning for connection from Matt...\n", logLevel.INFO);
		c = sizeof(struct sockaddr_in);
		/*create struct client and wait an incomming connection*/
		client = addSockaddr_in();  
		

		acceptedSocket = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);
		write(acceptedSocket , "Password : ?...\n" , strlen("Password : ?...\n")); /*ask passord*/

		
		if (recv(acceptedSocket, admin_message, 512, 0) > 0)
		{
			formatMessage(admin_message, &msg);
			if (strcmp(msg,"coucou") == 0 )
			{
				char *helloMessage = "[SIMEON] : Hello Matt...\n";
				write(acceptedSocket , helloMessage , strlen(helloMessage)); /*send that the password is not correct*/
				plog("Matt is here !...\n", logLevel.INFO);	
			}
			else
			{
				char *gtfoMessage = "[SIMEON] : You are not Matt...\n";
				write(acceptedSocket , gtfoMessage , strlen(gtfoMessage)); /*send that the password is not correct*/
				while (deleteClient(&acceptedSocket) == -1);	
			}
		}
		memset(admin_message ,0 , 512);  /*clear the variable*/
		
		/*Receive a message from admin*/
		while( (recv(acceptedSocket , admin_message , 512 , 0)) > 0 )
		{
			if (strlen(admin_message) > 2) /*if the message is not empty*/
			{
				formatMessage(admin_message, &msg);
				if (strcmp(msg, "exit") == 0)
				{	
					char *byeMessage = "[SIMEON] : Disconnected ...BYE Matt\n";
					write(acceptedSocket , byeMessage , strlen(byeMessage)); /*send Bye Message*/
					while (deleteClient(&acceptedSocket) == -1)
					break;
				}
				memset(admin_message ,0 , 512);  /*clear the variable*/
			}
		}
	}
	free(admin_message);
	return NULL;
}


