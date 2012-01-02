#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static int heap[100];
static heapsize;

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

void heapify(int *heap,int root)
{
	int l,r,largest;

	l = left(root);
	r = right(root);

	if((l <= heapsize) && (heap[l] > heap[root])) 
		largest = l;
	else 
		largest = root;
	if((r <= heapsize) && (heap[r] > heap[largest])) 
		largest = r;
	if(largest != root)  {
		swap(&heap[root],&heap[largest]);
		heapify(heap,largest);
	}
}

void build_heap(int *heap)
{
	int i;
	for(i = heapsize/2; i >= 1; i--) {
		heapify(heap,i);
	}
}

void heapsort(int *heap)
{
	int i;
	build_heap(heap);
	int heap_size = heapsize;
	printf("###########first heap##################\n");
	printf("heapsize = %d\n",heapsize);
	for(i = 1; i < heapsize+1 ; i++) {
		printf("%d\n",heap[i]);
	}
	printf("######################################\n");
	for(i = heapsize; i >= 2; i--) {
		swap(&heap[i],&heap[1]);
		heapsize = heapsize - 1;
		heapify(heap,1);
	}
}

int main()
{
	int data;
	int i,index = 1;
	while(scanf("%d",&data) != EOF) {
		heap[index++] = data;
	}
	heapsize = index -1;
	heapsort(heap);
	printf("After heapsort \n");
	for(i = 1; i < index ; i++) {
		printf("%d\n",heap[i]);
	}
}
