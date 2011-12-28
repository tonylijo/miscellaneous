#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next;
};

/*creates a new node and return the pointer to 
 *that node to the caller
 *input <- integer data.
 *output <- pointer to newly created node which is allocated in stack.
 */
struct node *new(int data)
{
	struct node *temp;
	temp=(struct node *) malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	return temp;

}

/*builds a set {1,2,3} 
 * and return the pointer to that list 
 * output -> pointer to head of that list.
 */
struct node *BuildOneTwoThree()
{
	struct node *head = NULL;
	head = new(1);
	head->next = new(2);
	head->next->next = new(3);
	return head;
}

/*counts the no of elements in a list.
 *input <- pointer to the start of a list .
 *output -> the no of nodes in the list.
 */
int Length(struct node *head)
{
	int count = 0;
	while(head) {
		count++;
		head = head->next;
	}
	return count;
}

/*pushes an element of a given position in a list.
 *input <- a reference to the starting node of the list and a integer data.
 *output -> none.
 */
void push(struct node ** headRef,int newData)
{
	struct node *temp;
	temp = new(newData);
	temp->next = *headRef;
	*headRef = temp;
}

/*prints the no of elements in a list.
 *input <- the pointer to the starting node of a list.
 */
void print(struct node *head)
{
	while(head) {
		printf("data=%d\n",head->data);
		head=head->next;
	}
}

/*searches for an element in a list and return the position of that element  * that list .
 */
int Count(struct node *head,int searchFor)
{
	int count = 0;
	while(head) {
		if(head->data == searchFor) {
			count++;
		}
		head = head->next;
	}
	return count;
}

void CountTest()
{
	struct node *mylist = BuildOneTwoThree();
	int count = Count(mylist,2);
}


int GetNth(struct node *head,int index)
{
	int count = -1;
	while(head) {
		if(index == ++count) {
			return head->data;
		}
		head = head->next;
	}
	fprintf(stderr,"list index out of range\n");
}

void GetNthTest()
{
	struct node *mylist = BuildOneTwoThree();
	int lastnode = GetNth(mylist,2);
	printf("the data at index two is %d\n",lastnode);
}

void BasicsCaller()
{
	struct node *head;
	int len;
	head = BuildOneTwoThree();
	push(&head,13);
	push(&(head->next),42);
	
	len = Length(head);
}

void DeleteList(struct node **headRef)
{
	struct node *temp = *headRef,*temp1;
	while(temp) {	
		temp1 = temp->next;
		free(temp);
		temp = temp1;
	}
	*headRef = NULL;
}

void DeleteListTest()
{
	struct node *myList = BuildOneTwoThree();
	DeleteList(&myList);
}


int Pop(struct node **headRef)
{
	struct node *temp = *headRef;
	int data = temp->data;
	temp = temp->next;
	free(*headRef);
	*headRef = temp;
	return data;
}

void PopTest()
{
	struct node *head = BuildOneTwoThree();
	int a = Pop(&head);
	int b = Pop(&head);
	int c = Pop(&head);
	int len = Length(head);
}

void InsertNth(struct node **head,int index,int data)
{
	struct node *current;
	current = *head;
	prev = *head;
	int i = 0;
	while(current) {
		if(i == index) {
			prev->next = new(data);
			prev->next->next = current;
			i++;

		}else {
			prev = current;
			current = current->next;
		}
	}
}

void InsertNthTest()
{	
	struct node *head = NULL;
	InsertNth(&head,0,13);
	InsertNth(&head,1,42);
	InsertNth(&head,1,,5);

	DeleteList(&head);
}

int main(int argc,char *argv[])
{
	CountTest();
	GetNthTest();
	DeleteListTest();
	PopTest();
}
