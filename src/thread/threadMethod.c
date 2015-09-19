#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*A list of methods that can be used in a thread*/





void *connectionEtablished(int* client_sock)
{
int read_size;
char client_message[2000];

  //Receive a message from client
    while( (read_size = recv(*client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
	fprintf(stdout, "Message = %s", client_message);
        //write((int)client_sock , client_message , strlen(client_message));
    }


}
