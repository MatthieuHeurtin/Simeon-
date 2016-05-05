#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/types.h>
#include <sys/socket.h>
#include "../logs/log.h"
#include "../server/socketManager.h"
/*All this method are executed by a thread. This thread represents a connection with the client*/

#define RETURN_ERROR -1


/*PRIVATE use to exec a process*/ 
int execProcess(char** parameters)
{ 
	pid_t pid;
	pid = fork();
	if (pid == -1) /*if problem*/
	{
		plog("fork failed\n", 1);
		return 1;
	} 
	else if (pid>0) /*parents*/ 
	{
		int status;
		waitpid(pid, &status, 0);
		return 1;
	}
	else  /*child*/
	{
		fprintf(stdout, "Command = %s\n", parameters[0]);
		if (execvp(parameters[0], parameters) == -1) /*if there is an error*/
		{
			plog("execvp failed\n", 1);
			return -1;
		}
	}
	return 0;
}

/*PRIVATE disconnect a client*/
int deleteClient(int *client_sock)
{
	char * msg;
	if (close(*client_sock) != 0)
	{
		msg= calloc(64, sizeof(char));
		sprintf(msg, "Cannot close socket %d\n", *client_sock);
		plog(msg, 1);
		free(msg);
		return -1;
	}
	plog("Socket closed\n", 0);
	return 0;
}

/*PRIVATE return a char* which contains parameters*/
char** getParameters(char* msg)
{
	char *p;
	int number_of_parameters=1;
	int i = 0;
	char **parameters;
	/*count number of parameters*/
	while (msg[i] != '\0')
	{
		if (msg[i] == 32)
		{
			number_of_parameters++;
		}
		i++;
	}

	/*alloc tab for parameters*/
	i=0;
	parameters = calloc(number_of_parameters, sizeof(char*));
	for(i = 0 ; i < number_of_parameters ; i++)
	{
		parameters[i] = calloc(1, sizeof(char)*10); 
	}

	i =0;
	for (p = strtok(msg," "); p != NULL; p = strtok(NULL, " "))
	{
		strcpy(parameters[i] , p);
		i++;
	}

	for(i = 0 ; i < number_of_parameters ; i++)
	{
   		printf("param = %s\n" , parameters[i]); 
	}
	
	return parameters;
}

/*PRIVATE format a message from telnet*/
char * formatMessage(char * client_message)
{
	/*format command and parameters */
	int size = strlen(client_message) - 2;
	char * msg = calloc(size, sizeof(char));
	strncpy(msg, client_message, size); /*delete the \r\n put by telnet*/
	return msg;
}

/*PUBLIC read command form client*/
void *connectionEtablished(void* client)
{
	int * client_sock = (int*)client;
	int read_size;
	char client_message[512];
	char ** command;
	char * msg;
	/*Receive a message from client*/
	while( (read_size = recv(*client_sock , client_message , 512 , 0)) > 0 )
	{
		
		msg = formatMessage(client_message);
		if (strlen(client_message) > 2) /*if the message is not empty*/
		{
			if (strcmp(msg, "exit") == 0)
			{	
				char *byeMessage = "[SIMEON] : Disconnected ...BYE\n";
				write(*client_sock , byeMessage , strlen(byeMessage)); /*send Bye Message*/
				deleteClient(client_sock);/*TODO check when the socket cannot be closed*/
				break;
			}

			command = getParameters(strdup(msg));
			if ( execProcess(command) == -1) /*if the execvp failed, the new process (child) is going to respond -1*/
			{
				char *forkFailedMessage= calloc(strlen(client_message) - 2 + 40, sizeof(char));
				sprintf(forkFailedMessage, "[SIMEON] : Your command '%s' is incorrect\n", msg);
				write(*client_sock , forkFailedMessage , strlen(forkFailedMessage)); /*send fork failed Message*/
				free(forkFailedMessage);
				exit(0); /*exit the current (child) process*/
			}
			memset(client_message ,0 , 512);  /*clear the variable*/
		}
	}
return NULL;
}



/*PUBLIC wait for admin connection*/
void *listenAdmin(void *port)
{
	int listener_sock;
	char admin_message[512];
	int read_size;	
	char * msg;
	int c;
	int acceptedSocket;
	struct sockaddr_in *client;
	LogLevel logLevel = initLoggerLevel();
	

	 /*connect on this socket if you want to admin Simeon*/

	listener_sock = createPassiveSocket((int)port);

	while (1)
	{
		plog("Start listenning for an admin connection...\n", logLevel.INFO);
		c = sizeof(struct sockaddr_in);
		/*create struct client and wait an incomming connection*/
		client = addSockaddr_in();  
		acceptedSocket = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);
		write(acceptedSocket , "Hello Matt" , strlen("Hello Matt")); /*write elcome*/
	
		/*Receive a message from admin*/
		while( (read_size = recv(acceptedSocket , admin_message , 512 , 0)) > 0 )
		{
			msg = formatMessage(admin_message);
			if (strlen(admin_message) > 2) /*if the message is not empty*/
			{
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
	return NULL;
}


