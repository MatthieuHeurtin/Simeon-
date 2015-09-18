#include<sys/socket.h>
#include<arpa/inet.h> 

/* represent an incoming client*/





/*configure an ip_address*/
void createAddr(struct sockaddr_in *server, int port, char* ip_addr);

struct sockaddr_in *addSockaddr_in();
