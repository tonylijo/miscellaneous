#include<unistd.h>
#include<stdio.h>
 
int main(int argc,char *argv[])
{
  int pid;
  pid = fork();
  if(pid == 0) {
    printf("i am child\n");
  } else {
    printf("I am parent \n");
  }
}
