#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *A,int left, int right)
{
	int pivot,i,j;
	pivot = A[left];
	i = left + 1;
	j = right;
	while(i < j) {
		while((A[i] < pivot) && (i < right)) 
				i++;
		
		while((A[j] > pivot) && (i < j)) 
				j--;

		swap(&A[i],&A[j]);
	}
	swap(&A[j],&A[left]);
	return j;
}
		

void quicksort(int *A,int left,int right)
{
	int pos,i;
	if(left < right) {
		pos = partition(A,left,right);
		quicksort(A,left,pos-1);
		quicksort(A,pos+1,right);
	}
}

int main(int argc,char *argv[])
{
	int i;
	int A[100];
	int index = 0;
	int data;
	while(scanf("%d",&data) != EOF) {
		A[index++] = data;
	}
	index--;
	quicksort(A,0,index);
	for(i = 0; i <= index; i++) 
		printf("%d\n",A[i]);
}
