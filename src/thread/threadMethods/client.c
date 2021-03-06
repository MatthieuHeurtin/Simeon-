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
#include "threadMethod.h"
#include "../../global_context/global_variables.h"


/*All this method are executed by a thread. This thread represents a connection with the client*/
void *connectionEtablished(void* void_context)
{
	int read_size;
	char client_message[512];
	char ** command;
	char * msg= NULL;
	Context context = (Context)void_context;
	Client current_client = *((Client*)GetLastAdded(context->connected_clients));
	int * client_sock = &current_client.id;

	/*Receive a message from client*/
	while( ((read_size = recv(*client_sock , client_message , 512 , 0)) > 0) && context->adminThread_event )
	{
		if (strlen(client_message) > 2) /*if the message is not empty*/
		{
			formatMessage(client_message, &msg);
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
	free(command);
	free(msg);
	deleteClient(client_sock);
	return NULL;
}

