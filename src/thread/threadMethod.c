#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

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
		char *argv[2];
		strcpy(argv[0], command);
		argv[1] = NULL;
		fprintf(stdout, "Command = %s\n", argv[0]);
		execvp(argv[0], argv);
	}
	else //parents 
	{
		fprintf(stdout, "I am the parent\n"); 
		int status;
		waitpid(pid, &status, 0);
	}
}


/*read command form client*/
void *connectionEtablished(int* client_sock)
{
int read_size;
char client_message[2000];

  //Receive a message from client
    while( (read_size = recv(*client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
	//fprintf(stdout, "Command = %s", client_message);
	execProcess(client_message);

    }
}







