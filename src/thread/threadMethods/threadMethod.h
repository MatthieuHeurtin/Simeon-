int execProcess(char** parameters);
int deleteClient(int *client_sock);
char** getParameters(char* msg);
/*Remove \r\n at the end of a string*/
void formatMessage(char * client_message, char** formated_message);
