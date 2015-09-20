#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */


//All this method are executed by a thread. This thread represent a connection with the client

void execProcess(char* command)
{ 
	pid_t parent = getpid();
	pid_t pid = fork();
	if (pid == -1) //if problem
	{
	    fprintf(stderr, "fork failed\n");
	} 
	else if (pid == 0) //child
	{
   char *argv[] = {command, (char *) 0 };

	 

		fprintf(stdout, "Command = %s\n", argv[0]);
		execvp(argv[0], argv);
	}
	else //parents 
	{
		fprintf(stdout, "I am the parent\n"); 
		int status;
		waitpid(pid, &status, 0);
		free(command);
	}
}


/*read command form client*/
void *connectionEtablished(int* client_sock)
{
int read_size;
char client_message[512];

  //Receive a message from client
    while( (read_size = recv(*client_sock , client_message , 512 , 0)) > 0 )
    {
	//format command
	int size = strlen(client_message) - 2;
	char * msg = calloc(strlen(client_message)-2, sizeof(char));
	strncpy(msg, client_message, size);
	execProcess(msg);
        memset(client_message ,0 , 512);  //clear the variable

    }
}







