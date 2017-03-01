#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "../logs/log.h"

void handle_SIGINT(int sig)
{
	if (sig == SIGINT)
	{
		printf("you can't kill me\n");
	}
}

void handle_signal()
{
	LogLevel logLevel = initLoggerLevel();
	
	if (signal(SIGINT, handle_SIGINT) == SIG_ERR)
	{
		plog("[handler.c] Can't subscribe to SIGINT signal\n", logLevel.WARNING);
	}
}
