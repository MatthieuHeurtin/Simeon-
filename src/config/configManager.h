/*struct that represents Simeon's config*/
struct configuration
{
	int DEFAULT_PORT;
	int VERBOSE; /*if 0 verbose == false, true ptherwise*/
};
typedef struct configuration Config;

/*load config*/
Config loadConfig();

/*display config*/
void showConfig(Config config);
