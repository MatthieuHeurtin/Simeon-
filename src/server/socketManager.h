#include<sys/socket.h>
#include<arpa/inet.h> 

/* represent an incoming client*/
struct client
{
	int id;
	

};
typedef struct cient Client;




/*configure an ip_address*/
void createAddr(struct sockaddr_in *server, int port, char* ip_addr);

struct sockaddr_in *addSockaddr_in();
