#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node {
	int data;
	struct node *next;
};

struct node *front,*rear;

struct node *new(int data)
{
	struct node *temp;
	temp = (struct node *) malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void enqueue(data)
{
	struct node *temp;
	if(rear == NULL) 
		front = rear = new(data);
	else {
		temp = new(data);
		temp->next = rear;
		rear = temp;
	}
}

struct node *find_front()
{
	struct node *temp = rear,*prev = NULL;
	while(temp->next) {
		perv = temp;
		temp = temp->next;
	}
	return prev;
}

int dequeue(data)
{
	struct node *newfront;
	if(rear == NULL) {
		printf("queue empty\n");
	} else {
		if(front == rear) {
			free(rear);
			front = rear = NULL;
		} else {
			newfront = find_front();
			newfront 
