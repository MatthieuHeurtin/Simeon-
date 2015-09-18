#include<sys/socket.h>
#include<arpa/inet.h> 

/*configure an ip_address*/
void createAddr(struct sockaddr_in *server, int port, char* ip_addr);

struct sockaddr_in *addSockaddr_in();
