enum Level {
INFO,
WARNING,
ERROR};

struct LogLevel
{
	int INFO;
	int WARNING;
	int ERROR;
};
typedef struct LogLevel LogLevel;

/*log in file*/
/*void flog(char * msg);*/

/*log on stdout*/
void plog(char *msg, enum Level level);


/*init a logger*/
LogLevel initLoggerLevel();



