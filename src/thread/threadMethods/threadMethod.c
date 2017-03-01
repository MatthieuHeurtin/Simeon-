#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/types.h>
#include <sys/socket.h>
#include "../../logs/log.h"
#include "../../server/socketManager.h"

#define RETURN_ERROR -1


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

int deleteClient(int *client_sock)
{
	LogLevel log = initLoggerLevel();
	char * msg = calloc(64, sizeof(char));
	if (close(*client_sock) != 0)
	{
		sprintf(msg, "Cannot close socket %d\n", *client_sock);
		plog(msg, log.WARNING);
		free(msg);
		return -1;
	}
	sprintf(msg, "Socket closed %d\n", *client_sock);
	plog(msg, log.INFO);
	free(msg);
	return 0;
}

char** getParameters(char* msg)
{
	char *p;
	int number_of_parameters=1;
	int i = 0;
	char **parameters;
	/*count number of parameters*/
	while (msg[i] != '\0')
	{
		if (msg[i] == 32) /*32 = space*/
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


void formatMessage(char * client_message, char ** formated_message)
{
	/*format command and parameters */
	int size = strlen(client_message) - 2;
	free(*formated_message);
	*formated_message = calloc(size, sizeof(char));
	strncpy(*formated_message, client_message, size); /*delete the \r\n put by telnet*/
}




