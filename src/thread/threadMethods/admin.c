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
#include <pthread.h>

#define RETURN_ERROR -1

/*All this method are executed by a thread. This thread represents a connection with the client*/


/*PRIVATE*/
void ask_password(int acceptedSocket, LogLevel logLevel)
{
	char* admin_message = calloc(512, sizeof(char));
	char *msg = NULL;
	write(acceptedSocket , "Password : ?...\n" , strlen("Password : ?...\n")); /*ask passord*/
	
	if (recv(acceptedSocket, admin_message, 512, 0) > 0)
	{
		formatMessage(admin_message, &msg);
		if (strcmp(msg,"coucou") == 0 )
		{
			char *helloMessage = "[SIMEON] : Hello Matt...\n";
			write(acceptedSocket , helloMessage , strlen(helloMessage)); /*send passwrod is correct*/
			plog("Matt is here !...\n", logLevel.INFO);
		}
		else
		{
			char *gtfoMessage = "[SIMEON] : You are not Matt...\n";
			write(acceptedSocket , gtfoMessage , strlen(gtfoMessage)); /*send password is incorrect*/
			while (deleteClient(&acceptedSocket) == -1);	
		}
	}
	free(admin_message);
}

/*PRIVATE*/
void connection_openned(int acceptedSocket, int * continu)
{
	char* admin_message = calloc(512, sizeof(char));
	char *msg = NULL;
	while( (recv(acceptedSocket , admin_message , 512 , 0)) > 0 )
	{
		if (strlen(admin_message) > 2) /*if the message is not empty*/
		{
			formatMessage(admin_message, &msg);
			if (strcmp(msg, "exit") == 0)
			{	
				char *byeMessage = "[SIMEON] : Disconnected ...BYE Matt\n";
				write(acceptedSocket , byeMessage , strlen(byeMessage)); /*send Bye Message*/
				while (deleteClient(&acceptedSocket) == -1);
				break;
			}
			else if (strcmp(msg, "bye") == 0)
			{	
				char *dieMessage = "[SIMEON] : You want me to die ...BYE Matt\n";
				write(acceptedSocket , dieMessage , strlen(dieMessage)); /*send Bye Message*/
				while (deleteClient(&acceptedSocket) == -1);
				*continu = 0;
				break;
			}
			memset(admin_message ,0 , 512);  /*clear the variable*/
		}
	}
	free(admin_message);
}


/*PUBLIC*/
void *listenAdmin(void *port)
{
	int listener_sock;
	int c;
	int acceptedSocket;
	struct sockaddr_in *client;
	LogLevel logLevel = initLoggerLevel();
	int continu = 1;

	 /*connect on this socket if you want to admin Simeon*/
	listener_sock = createPassiveSocket((int)port);
	
	if (listener_sock != RETURN_ERROR)
	{
	pthread_cleanup_push(deleteClient, &listener_sock);
		while (continu)
		{
			plog("[admin.c] Start listenning for connection from Matt...\n", logLevel.INFO);
			c = sizeof(struct sockaddr_in);
			/*create struct client and wait an incomming connection*/
			client = addSockaddr_in();  
			acceptedSocket = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);
			
			/*ask identification*/			
			ask_password(acceptedSocket, logLevel);
		
			/*Receive a message from admin*/
			connection_openned(acceptedSocket, &continu);
		}

	pthread_cleanup_pop(1); /*free the passive socket*/
	}	
	return NULL;
}



