#include"log.h"
#include<stdio.h>
#include<stdlib.h>

/*log in file (file log)*/
void flog(char * msg)
{
	

}

/*log on stdout (print log)*/
void plog(char *msg, enum Level level)
{
	switch(level)
	{
		case INFO:
		fprintf(stdout, "[INFO] : %s", msg);
		break;
		case WARNING:
		fprintf(stdout, "[WARNING] : %s", msg);
		break;
		case ERROR:
		fprintf(stderr, "[ERROR] : %s", msg);
		break;
		default:
		break;
	}

}

