#include"log.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../config/configManager.h"

/*log in file (file log) */
void flog(char * msg)
{
	Config conf = loadConfig();
	FILE *file = fopen(conf.LOGS_PATH, "a+");
	if (file != NULL)
	{
		fprintf(file, "%s",msg);
	}
	fclose(file);
}


/*log on stdout (print log)*/
void plog(char *msg, enum Level level)
{
	if (msg == NULL)
	{
		return;
	}
	char *message_to_write = calloc(1024, sizeof(char));
	switch(level)
	{	
		case INFO:
		sprintf(message_to_write, "[INFO] : %s", msg);
		fprintf(stdout, message_to_write);		
		break;
		case WARNING:
		sprintf(message_to_write, "[WARNING] : %s", msg);
		fprintf(stdout, message_to_write);		
		break;
		case ERROR:
		sprintf(message_to_write, "[ERROR] : %s", msg);
		fprintf(stderr, message_to_write);
		break;
		default:
		break;
	}
	flog(message_to_write);
	free(message_to_write);
}

/*init a logger*/
LogLevel initLoggerLevel()
{
	LogLevel logLevel;
	logLevel.INFO = 0;
	logLevel.WARNING = 1;
	logLevel.ERROR = 2;
	return logLevel;
}

