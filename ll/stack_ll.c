#include<stdio.h>
#include<stdlib.h>
struct node {
	int data;
	struct node *next;
};

static struct node *head;

struct node *new(int data)
{
	struct node *temp ;
	temp = (struct node *) malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void display(struct node *head)
{
	struct node *temp = head;
	if(temp) {
		printf("|%d|\n",temp->data);
		printf("###\n");
		display(temp->next);
	} else {
		printf("###\n");
	}
}

void push(data)
{
	struct node *temp;
	if(head == NULL)  {
		head = new(data);
	} else {
		temp = new(data);
		temp->next = head;
		head = temp;
	}
}

int pop(void)
{
	int data;
	struct node *temp;
	if(head == NULL) {
		printf("cannot pop stack empty");
		return -1;
	} else {
		data = head->data;
		temp = head;
		head = head->next;
		free(temp);
		return data;
	}
}

int main(int argc,char *argv[])
{
	int data,choice;
	do {
		printf("Enter your choice\n" 
				"1.push\n"
				"2.pop\n"
				"3.display\n"
				"4.exit\n"
			"choice no:");
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				printf("##########push############\n");
				printf("Enter the no :");
				scanf("%d",&data);
				push(data);
				printf("#########################\n");
				break;
			case 2:
				printf("########pop###############\n");
				data = pop();
				printf("data = %d\n",data);
				printf("#########################\n");
				break;
			case 3: 
				printf("#########################\n");
				display(head);
				printf("#########################\n");
				break;
			case 4:
				exit(0);
		}
	}while(1);
}
