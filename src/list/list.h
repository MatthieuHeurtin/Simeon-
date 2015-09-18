
//this struc is a list
struct list
{
	int element;
	struct list * next;

};
typedef struct list* List;

List createList();
List addElement(List l, int element);
void showList(List l);




