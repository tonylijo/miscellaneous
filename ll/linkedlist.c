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
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new(data);
	}
	return head;
}

void print(struct node *head)
{
	while(head != NULL) {
		printf("%d \n",head->data);
		head = head->next;
	}
}

int main(int argc,char *argv[])
{
	int i;
	struct node *head = NULL;
	int data;
	while(scanf("%d",&data) != EOF) {
		head = append(head,data);
	}
	print(head);
}
