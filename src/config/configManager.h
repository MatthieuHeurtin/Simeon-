/*struct that represents Simeon's config*/
struct configuration
{
	int DEFAULT_PORT;
	int VERBOSE; /*if 0 verbose == false, true ptherwise*/
	int CONTROL_PORT;
	char * LOGS_PATH;
	char * DEFAULT_NAME;
};
typedef struct configuration Config;

/*load config*/
Config loadConfig();

/*display config*/
void showConfig(Config config);
