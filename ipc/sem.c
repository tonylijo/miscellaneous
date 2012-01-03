#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int main(int argc,char *argv[])
{
  int semid;
  semid = semget(11,8,0666|IPC_CREAT);
  printf("%d\n",semid);
}
