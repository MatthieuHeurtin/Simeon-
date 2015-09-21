/*struct that represents Simeon's config*/
struct configuration
{
	char* DEFAULT_IP;
	int DEFAULT_PORT;
};
typedef struct configuration Config;

/*load config*/
Config loadConfig();
