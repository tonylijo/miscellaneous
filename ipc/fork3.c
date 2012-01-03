#include<unistd.h>
#include<stdio.h>
int data = 10;

int main(int argc,char *argv[])
{
  int pid;
  if(pid == 0) {
    data = 20;
  } else {
    sleep(5);
    printf("%d\n",data);
  }
}
