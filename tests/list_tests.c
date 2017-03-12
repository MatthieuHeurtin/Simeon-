#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include "../src/list/list.h"


/*This class is used to test if the file list.c works*/
List testCreateList()
{
	fprintf(stdout, "TEST : createlist()\n");
	List l = createList();
	if (l != NULL)
	{
		fprintf(stderr, "ERROR : The created list should be NULL\n");
		exit(-1);
	}
	fprintf(stdout, "... OK\n");
	return l;
}

void testAddElement(List l)
{
	int integer = 69;
	fprintf(stdout, "TEST:  addElement()\n");
	l = addElement(l, &integer);
	if (l == NULL)
	{
		fprintf(stderr, "ERROR : The list should not be NULL\n");
		exit(-1);
	}
	if ((*(int*)(l->element)) != integer)
	{
		fprintf(stderr, "ERROR : The element should be %d\n",integer);
		exit(-1);
	}
	if (l->next != NULL)
	{
		fprintf(stderr, "ERROR : The next should be NULL\n");
		exit(-1);
	}
	fprintf(stdout, "... OK\n");
}


void testAddElements(List l)
{
	int integer = 69;
	char character= 67;
	fprintf(stdout, "TEST:  addElements\n");
	l = addElement(l, & integer);
	l = addElement(l, &character);
	/*test first element (last added)*/
	if (l == NULL)
	{
		fprintf(stderr, "ERROR : The list should not be NULL\n");
		exit(-1);
	}
	if ((*(char*)(l->element)) != character)
	{
		fprintf(stderr, "ERROR : The element should be %c\n",character);
		exit(-1);
	}
	if (l->next == NULL)
	{
		fprintf(stderr, "ERROR : The next should not be NULl\n");
		exit(-1);
	}
	
	/*Test last element (first added)*/
	if (l->next == NULL)
	{
		fprintf(stderr, "ERROR : The next should not be NULl\n");
		exit(-1);
	}
	if (*((int*)(l->next->element)) != integer)
	{
		fprintf(stderr, "ERROR : The element should be %d\n", integer);
		exit(-1);
	}
	fprintf(stdout, "... OK\n");
}
void test_GetLastAdded(List l)
{
	int integer1 = 69;
	int integer2= 67;
	fprintf(stdout, "TEST:  GetLastAdded()\n");
	l = addElement(l, &integer1);
	l = addElement(l, &integer2);
	void* value = GetLastAdded(l);
	if ((*(int*)value) != integer2)
	{
		fprintf(stderr, "ERROR : The element should be %d but was %d\n", integer2, (*(int*)value));
		exit(-1);
	}
	fprintf(stdout, "... OK\n");
}





int main(int argc, char** argv)
{
	
	List l;

	l = testCreateList();
	testAddElement(l);
	testAddElements(l);
	test_GetLastAdded(l);	

	/*l = addElement(l, 70);
	l = addElement(l, 71);
	l = addElement(l, 72);
	l = addElement(l, 73);
	*/
	showList(l, printChar);
	return 0;
}
