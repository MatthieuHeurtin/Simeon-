#include <stdio.h>
#include <stdlib.h>
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
	List q;
	if (l == NULL)
	{
		l = calloc(1, sizeof(l));
		l->element = element;
		l->next = NULL;
		return l;
	}
	q = calloc(1, sizeof(*q));
	q->element = element;
	q->next = l;
	return q;
}

void * GetLastAdded(List l)
{
	if (l==NULL)
	{
		return NULL;
	}
	else
	{
		return l->element;
	}
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
