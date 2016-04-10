#include <stdio.h>
#include <stdlib.h>
#include "../server/socketManager.h"
#include "list.h"

/*used to create a list*/
List createList()
{
	List l = NULL;
	return l;
}


/*used to add an element*/
List addElement(List l, void* element)
{
	List q = calloc(1, sizeof(*q));
	q->element = element;
	q->next = l;
	return q;
}


void printInt(void * element)
{
	int * value = (int*)element;
	fprintf(stdout, "Element = %d\n", *value);
}
void printChar(void * element)
{
	char * value = (char*)element;
	fprintf(stdout, "Element = %d\n", *value);
}
void printClient(void * element)
{
	Client * value = (Client*)element;
	fprintf(stdout, "Element id= %d\n", value->id);
}



/*used to display all elements*/
void showList(List l, void (*function) ())
{
	List tmp = l;
	while (tmp != NULL)
	{
		function(tmp->element);
		tmp = tmp->next; 
	}
}
