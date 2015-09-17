#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr

void createAddr(struct sockaddr_in* server ,int port, char* ip_addr)
{
	(*server).sin_family = AF_INET;
	(*server).sin_port = htons(port);
	inet_aton(ip_addr, &(*server).sin_addr);
}
