#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char* readFromOneFile(char* path)
{
	//check if exists
	if (exist(path) != 0)
	{
		return NULL;
	}
	

	char * buff = malloc( 255 * sizeof(char)); //alloc a buffer of 255 TODO count number of char in the file
	if (buff == NULL)
	{	
		//TODO ERROR MSG
		return NULL;
	}
	FILE * file = fopen( path, "r" );
	fscanf(file, "%s", buff); //read the file
	fclose(file);
	return buff;
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
