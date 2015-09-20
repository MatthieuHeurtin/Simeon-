#include<sys/socket.h>
#include<arpa/inet.h> /*inet_addr*/
#include <stdlib.h>
#include <netinet/in.h>



/*configure an ip_address*/
void createAddr(struct sockaddr_in* server ,int port, char* ip_addr)
{
	(*server).sin_family = AF_INET;
	(*server).sin_port = htons(port);
	inet_aton(ip_addr, &(*server).sin_addr);
}


/*create a new sockaddr client*/
struct sockaddr_in *addSockaddr_in()
{
	struct sockaddr_in *newSockaddr_in = (struct sockaddr_in *)calloc(1 ,sizeof(struct sockaddr_in));
	return newSockaddr_in;

}
