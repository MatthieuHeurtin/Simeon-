#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include "../logs/log.h"
#include "configManager.h"
/*load the config*/
Config loadConfig()
{
	char path[24] = "./Simeon.conf";
	FILE *file;	
	char *name;
	char *value;
	Config conf;
	file = fopen(path, "r");

	name = calloc(24,sizeof(char));
	value = calloc(24, sizeof(char));
	while (fscanf(file, "%s", name) != EOF) 
	{
		
		if (strstr(name, "#") != NULL)  /*check if it is a comment*/
		{
			while(fgetc(file) != '\n'); /*until the next line*/
		}
		else /*if it is not a  comment*/
		{
			fscanf(file, "%s", value);
			/*in function of parameter*/
			if (strcmp(name, "DEFAULT_PORT") == 0)
			{
				conf.DEFAULT_PORT = atoi(value); /*TODO verify PORT VALUE*/
			} 			
			else if (strcmp(name, "VERBOSE") == 0)
			{
				conf.VERBOSE = atoi(value); /*TODO verify PORT VALUE*/
			} 
		}
		memset(name, 0, 24);
		memset(value,0, 24);
	

	}	
	free(name);
	free(value);
	return conf;
}


void showConfig(Config config)
{
	
	char *msg;
	plog("====DISPLAY SIMEON CONFIG==== \n", 0);
	msg= calloc(64, sizeof(char));
	sprintf(msg, "DEFAULT_PORT %d\n", config.DEFAULT_PORT);
	plog(msg, 0);
	
	memset(msg, 0, 64);
	
	sprintf(msg, "VERBOSE %d (if 0 == FALSE, TRUE otherwise)\n", config.VERBOSE);
	plog(msg, 0);
	plog("============================= \n", 0);
	free(msg);





}



