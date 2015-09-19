#include<stdlib.h>
#include<stdio.h>
#include<string.h>   
#include<unistd.h>   
#include "../src/list/list.h"





int main(int argc, char** argv)
{
	//TEST list
	int p = 78;
	char i= 67;
	List l = createList();
	l = addElement(l, &p);
	l = addElement(l, &i);
	/*l = addElement(l, 70);
	l = addElement(l, 71);
	l = addElement(l, 72);
	l = addElement(l, 73);
	*/
	showList(l, printChar);
	return 0;
}
