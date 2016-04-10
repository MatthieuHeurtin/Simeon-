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

	name = calloc(512,sizeof(char));
	value = calloc(512, sizeof(char));
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
				conf.VERBOSE = atoi(value); /*TODO verify VALUE*/
			} 
			else if (strcmp(name, "CONTROL_PORT") == 0)
			{
				conf.CONTROL_PORT = atoi(value); /*TODO verify VALUE*/
			} 
			else if (strcmp(name, "LOGS_PATH") == 0)
			{
				conf.LOGS_PATH = calloc(1024, sizeof(char));
				strcpy(conf.LOGS_PATH, value); /*TODO verify VALUE*/
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
	LogLevel logLevel = initLoggerLevel();
	char *msg;
	plog("==== DISPLAY SIMEON CONFIG ==== \n", logLevel.INFO);
	msg= calloc(64, sizeof(char));
	sprintf(msg, "DEFAULT_PORT = %d\n", config.DEFAULT_PORT);
	plog(msg, logLevel.INFO);
	memset(msg, 0, 64);
	
	sprintf(msg, "VERBOSE = %d\n", config.VERBOSE);
	plog(msg, logLevel.INFO);
	memset(msg, 0, 64);

	sprintf(msg, "CONTROL_PORT = %d\n", config.CONTROL_PORT);
	plog(msg, logLevel.INFO);
	memset(msg, 0, 64);

	sprintf(msg, "LOGS_PATH = %s\n", config.LOGS_PATH);
	plog(msg, logLevel.INFO);
	memset(msg, 0, 64);
	plog("=============================== \n", 0);
	free(msg);
}



