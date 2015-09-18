
#include <stdio.h>
#include <stdlib.h>


#include "list.h"

//used to create a list
List createList()
{
	List l = NULL;
	return l;
}


//used to add an element
List addElement(List l, int element)
{
	List q = calloc(1, sizeof(*q));
	q->element = element;
	q->next = l;
	return q;
}





//used to display all elements
void showList(List l)
{
	List tmp = l;
	while (tmp != NULL)
	{
		fprintf(stdout, "Element = %d\n", tmp->element);
		tmp = tmp->next; 


	}
}
