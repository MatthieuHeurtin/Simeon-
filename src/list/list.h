/*this struc is a list*/
struct list
{
	void* element;
	struct list * next;

};
typedef struct list* List;

List createList();
List addElement(List l, void* element);
void showList(List l, void (*function) ());
void * GetLastAdded(List l);



/*list of print function (used for debug)*/
void printInt(void * element);
void printChar(void * element);



