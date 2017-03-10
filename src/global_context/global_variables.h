#include "../config/configManager.h"
#include "../list/list.h"

struct global_context
{
	int nb_client;
	Config conf;
	List connected_clients;
	int adminThread_event;
};
typedef struct global_context* Context;


/* represent an incoming client*/
struct client
{
	int id;
	char *name;

};
typedef struct client Client;
