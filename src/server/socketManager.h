#include<sys/socket.h>
#include<arpa/inet.h> 

/*configure an ip_address*/
void createAddr(struct sockaddr_in *server, int port);

struct sockaddr_in *addSockaddr_in();

/*Create a passive socket*/
int createPassiveSocket(int port);

