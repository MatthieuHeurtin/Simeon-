#include<stdlib.h>
#include<stdio.h>

void *threadMethod()
{
int i = 0;
while(i <10000)
{
fprintf(stdout , "I am the thread method\n");
}
}
