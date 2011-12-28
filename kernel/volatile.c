#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
int jiffies = 0;

void handler(int n)
{
	printf("called handler ...\n");
	jiffies++;
}

int main()
{
	signal(SIGINT,handler);
	while(jiffies<3);
}
