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
#include "../config/configManager.h"
/*All this method are executed by a thread. This thread represents a connection with the client*/


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
	return 1;
}

/*PRIVATE disconnect a client*/
int deleteClient(int *client_sock)
{
	char * msg;
	if (close(*client_sock) != 0)
	{
		msg= calloc(64, sizeof(char));
		sprintf(msg, "cannot close socket %d\n", *client_sock);
		plog(msg, 1);
		free(msg);
		return -1;
	}
	plog("Socket closed\n", 0);
	return 1;
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



/*PUBLIC read command form client*/
void *connectionEtablished(void* client)
{
	int * client_sock = (int*)client;
	int read_size;
	char client_message[512];
	char ** command;
	/*Receive a message from client*/
	while( (read_size = recv(*client_sock , client_message , 512 , 0)) > 0 )
	{

		if (strlen(client_message) > 2) /*if the message is not empty*/
		{
			/*format command and parameters */
			int size = strlen(client_message) - 2;
			char * msg = calloc(size, sizeof(char));
			strncpy(msg, client_message, size); /*delete the \r\n put by telnet*/

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
				char *forkFailedMessage= calloc(size + 40, sizeof(char));
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
void *listenAdmin(void* arg)
{
	plog("Start listenning for an admin connection...\n", 0);
	 /*connect on this socket if you want to admin Simeon*/
	struct sockaddr_in control_addr;
	int listener_sock;
	int socketToanwser;
	Config conf = loadConfig();
	LogLevel logLevel = initLoggerLevel();
	int isAnAdminConnected = 0;

	/*create server address*/
	createAddr(&control_addr, conf.CONTROL_PORT); 
	

	/*Create socket*/
	listener_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (listener_sock == -1)
	{
		plog("Could not create Listener_sock", logLevel.ERROR);
		return -1;
	}
	plog("Control_sock created\n", logLevel.INFO);

	/*Bind*/
	if( bind(listener_sock,(struct sockaddr *)&control_addr , sizeof(control_addr)) < 0)
	{
		/*print the error message*/
		plog("bind failed. Error\n", logLevel.ERROR);
		return -1;
	}
	plog("CONTROL Bind done\n", logLevel.INFO);

	/*sokcet is passive*/
	listen(listener_sock , 2);

	while (1)
	{
		
		int c = sizeof(struct sockaddr_in);

		/*create struct client and wait an incomming connection*/
		struct sockaddr_in *client = addSockaddr_in();  
		int acceptedSocket = accept(listener_sock, (struct sockaddr *)client, (socklen_t*)&c);

		if (isAnAdminConnected)
		{
			write(acceptedSocket , "An admin is already connected" , strlen("An admin is already connected"));
		}
		else
		{
			isAnAdminConnected = 1;
			write(acceptedSocket , "COUCOU MATT" , strlen("COUCOU MATT")); /*write elcome*/
		}
		

	}
	plog("Start listenning for an admin connection\n", 0);
	return NULL;
}


