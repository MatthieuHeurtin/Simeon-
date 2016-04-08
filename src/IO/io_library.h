/*read a file and return a char*, if any problem return NULL*/
char* readFromOneFile(char* path);

/*write at the end of a file, if it does not exist, create the file*/
int writeInFile(char* path, char* msg);

/*read current line in the file. Does not close the file*/
char* readLine(FILE *file);

/*Check if a file exists*/
int exist(char*path);
