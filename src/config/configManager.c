#include<stdlib.h>
#include<stdio.h>
#include "../IO/io_library.h"
#include "../logs/log.h"
#include "configManager.h"
/*load the config*/
Config loadConfig()
{
	char path[24] = "./Simeon.conf";
	FILE *file;	
	char *msg;
	int i;
	Config conf;
	file = fopen (path, "r" );
	msg = readLine(file); /*read first line*/
	while (msg != NULL)
	{
		i=0;
		while (msg[i] == 32) /*until the first character which is not a space*/
		{
			i++;
		}
		if (msg[i] != 35 ) /*if it is not a comment*/
		{
			plog(msg, 0);
			while(msg[i] != 61) /*until the symbol '=' */ 
			{
				i++;
			}
			i++;
			while (msg[i] == 32) /*until the first character which is not a space*/
			{
				i++;
			}
			if (msg[i] == 8 || msg[i] == 0 || msg[i] == 10 ) /*if it is "\b" or "\0" or "\n" */
			{
				plog("Cannot load the config file\n", 2);
				exit(-1);
			}
			
			
		}	
		msg = readLine(file);	
	}
	free(msg);
	return conf;
}

