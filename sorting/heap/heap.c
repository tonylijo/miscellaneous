#include<stdio.h>
#include<stdlib.h>
#define HEAPSIZE 100

int heap[HEAPSIZE];
int heapsize;

void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int parent(int index)
{
	return index/2;
}

int left(int index)
{
	return 2*index;
}

int right(int index)
{
	return 2*index + 1;
}

void heapify(int *heap,int index)
{
	int l,r,largest;
	l = left(index);
	r = right(index);

	if( (l <= heapsize) && (heap[l] > heap[index])) 
		largest = l;
	else
		largest = index;
	if(( r <= heapsize) && (heap[r] > heap[largest])) 
		largest = r;
	if(largest != index) {
		swap(&heap[index],&heap[largest]);
		heapify(heap,largest);
	}
}

int main()
{
	int data,index = 1,i,j;
	while(scanf("%d",&data) != EOF) {
		heap[index++] = data;
	}
	heapsize = index-1;
	printf("heapsize:%d\n",heapsize);
	for(i = 1; i < index; i++) 
		printf("index:%d:=%d\n",i,heap[i]);
	for(i = heapsize/2;i >= 1; i--) {
		printf("heapify(heap,%d)\n",i);
		heapify(heap,i);
		printf("#####################################\n");
		for(j = 1; j < index; j++) 
			printf("index:%d:=%d\n",j,heap[j]);
		printf("#####################################\n");
	}
		
	for(i = 1; i < index; i++) 
		printf("index:%d:=%d\n",i,heap[i]);
}
