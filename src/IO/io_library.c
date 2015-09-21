#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*check if a file exist, if not create it and return a pointer on it*/
int exist(char*path)
{
	if( access(path, F_OK ) != -1 ) 
	{
		return 0;
	} 
	else 
	{
		return -1;
	}
}



char* readFromOneFile(char* path)
{
	char * buff;
	FILE * file;
	/*check if exists*/
	if (exist(path) != 0)
	{
		return NULL;
	}
	

	buff= malloc( 255 * sizeof(char)); /*alloc a buffer of 255 TODO count number of char in the file*/
	if (buff == NULL)
	{	
		/*TODO ERROR MSG*/
		return NULL;
	}
	file = fopen( path, "r" );
	fscanf(file, "%s", buff); /*read the file*/
	fclose(file);
	return buff;
}

char* readLine(FILE *file)
{
	if (file != NULL) 
	{
		char *line = calloc(1024, sizeof(char));
		while(fgets(line,1024,file)!= NULL) /* read a line from a file */ 
		{
			return line;
		}
	}
	else 
	{
		/*TODO print the error message on stderr*/
	}
return NULL;
}

int writeInFile(char* path, char* msg)
{
	FILE * f = fopen(path, "w+");	
	if (f != NULL)
	{
		fprintf(f, "%s" , msg);
	}
	fclose(f);
	return 0;
}



