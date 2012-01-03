#include<unistd.h>
#include<stdio.h>

void child(int i)
{
  while(1) {printf("i am child %d \n",i);}
}

int main(int argc,char *argv[])
{
  int i,pid;
  for(i = 0; i < 5 ; i++) {
    pid = fork();
    if(pid == 0) child(i);
  }
  while(1);
}
