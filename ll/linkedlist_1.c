#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
	int data;
	struct node *next;
};

struct node *new(int data)
{
	struct node *temp;
	temp = (struct node *) malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

struct node *append(struct node *head,int data)
{
	struct node *temp = head;
	if(head == NULL) {
		return new(data);
	} else {
		temp->next = append(temp->next,data);
		return temp;
	}
}

struct node *print(struct node *head)
{
	if(head) {
		printf("%d\n",head->data);
		print(head->next);
	}
}

struct node *rev_ll(struct node *head) 
{
	struct node *temp;
	if(!head) return NULL;
	if(head->next == NULL ) {
		return head;
	} else {
		temp = rev_ll(head->next);
		head->next->next = head;
		head->next = NULL;
		return temp;
	}
}

int main()
{
	int data;
	struct node *head = NULL;
	while(scanf("%d",&data) != EOF) {
		head = append(head,data);
	}
	print(head);
	head = rev_ll(head);
	printf("________rev__________\n");
	print(head);
}
