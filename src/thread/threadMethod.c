#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/types.h>
#include <sys/socket.h>

/*All this method are executed by a thread. This thread represents a connection with the client*/


/*PRIVATE use to exec a process*/ 
int execProcess(char* command)
{ 
	char *argv[2];
	pid_t pid;
	argv[0] = command;
	argv[1] = NULL;
	pid = fork();
	if (pid == -1) /*if problem*/
	{
		fprintf(stderr, "fork failed\n");
		return 1;
	} 
	else if (pid>0) /*parents*/ 
	{
		int status;
		waitpid(pid, &status, 0);
		free(command);
		return 1;
	}
	else  /*child*/
	{
		 fprintf(stdout, "Command = %s\n", argv[0]);
		if (execvp(argv[0], argv) == -1) /*if there is an error*/
		{
			fprintf(stderr, "execvp failed\n");
			return -1;
		}
	}
return 1;
}

/*PRIVATE disconnect a client*/
int deleteClient(int *client_sock)
{
	if (close(*client_sock) != 0)
	{
		fprintf(stderr, "cannot close socket %d\n", *client_sock);
		return -1;
	}
	fprintf(stdout, "Socket closed\n");
	return 1;
}



/*PUBLIC read command form client*/
void *connectionEtablished(void* client)
{
	int * client_sock = (int*)client;
	int read_size;
	char client_message[512];
	/*Receive a message from client*/
	while( (read_size = recv(*client_sock , client_message , 512 , 0)) > 0 )
	{
		fprintf(stdout, "SIZE = %d\n", strlen(client_message));
		if (strlen(client_message) > 2) /*if the message is not empty*/
		{
			/*format command (useless when i will have a real client)*/
			int size = strlen(client_message) - 2;
			char * msg = calloc(strlen(client_message)-2, sizeof(char));
			strncpy(msg, client_message, size);

			if (strcmp(msg, "exit") == 0)
			{	
				char *byeMessage = "[SIMEON] : Disconnected ...BYE\n";
				write(*client_sock , byeMessage , strlen(byeMessage)); /*send Bye Message*/
				deleteClient(client_sock);/*TODO check when the cannot be closed*/
				break;
			}
			if ( execProcess(msg) == -1) /*if the execvp failed, the new process is going to respond*/
			{
				char *forkFailedMessage= calloc(size + 40, sizeof(char));
				sprintf(forkFailedMessage, "[SIMEON] : Your command '%s' is incorrect\n", msg);
				write(*client_sock , forkFailedMessage , strlen(forkFailedMessage)); /*send Bye Message*/
				free(forkFailedMessage);
				exit(0); /*exit the current process*/
			}
			memset(client_message ,0 , 512);  /*clear the variable*/
		}
	}
return NULL;
}







