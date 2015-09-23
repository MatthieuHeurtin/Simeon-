#include<sys/socket.h>
#include<arpa/inet.h> /*inet_addr*/
#include <stdlib.h>
#include <netinet/in.h>



/*configure an ip_address*/
void createAddr(struct sockaddr_in* server ,int port)
{
	(*server).sin_family = AF_INET;
	(*server).sin_port = htons(port);
	server->sin_addr.s_addr = htonl(INADDR_ANY);
}


/*create a new sockaddr client*/
struct sockaddr_in *addSockaddr_in()
{
	struct sockaddr_in *newSockaddr_in = (struct sockaddr_in *)calloc(1 ,sizeof(struct sockaddr_in));
	return newSockaddr_in;

}
