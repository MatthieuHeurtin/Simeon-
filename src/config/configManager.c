#include<stdlib.h>
#include<stdio.h>
#include "../IO/io_library.h"

/*load the config*/
int loadConfig()
{
	char path[24] = "./SimeonConfig.conf";
	FILE *file;	
	char *msg;
	file = fopen (path, "r" );
	msg = readLine(file);
	fprintf(stdout , "OOOO %s\n", msg);
	while (msg != NULL)
	{
		msg = readLine(file);
		fprintf(stdout , "OOOO %s\n", msg);
	}

	free(msg);
	return 0;
}

