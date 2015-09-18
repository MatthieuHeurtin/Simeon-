#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*A list of methods that can be used in a thread*/





void *connectionEtablished(int* client_sock)
{
int read_size;
char client_message[2000];

fprintf(stdout, "I am the thread method");
  //Receive a message from client
    while( (read_size = recv(*client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
	fprintf(stdout, "Message = %s Socket = %d\n ", client_message, *client_sock);
        //write((int)client_sock , client_message , strlen(client_message));
    }


}
