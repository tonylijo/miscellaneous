#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#define KEY 13
#define err_exit(msg) do{ perror(msg); exit(errno);}while(0)

void action(int semid,int sem_num,int sem_op)
{
  struct sembuf semops;
  semops.sem_num = sem_num;
  semops.sem_op = sem_op;
  semops.sem_flg = 0;
  if(semop(semid,&semops,1) == -1) 
    err_exit("semop: sennot do semoperattion");
}

void up(semid)
{
  action(semid,0,1);
}

void down(semid)
{
  action(semid,0,-1);
}

void critical(char *s)
{
  int i;
  for(i = 0; i < 5; i++) {
    printf("%s:%d\n",s,i);
    sleep(1);
  }
}

int main(int argc,char *argv[])
{
  int semid;
  semid = semget(KEY,1,IPC_CREAT|0666);
  assert(semid != -1);
  semctl(semid,0,SETVAL,1);
  if(fork() == 0) {
    while(1) {
      down(semid);
      critical("child");
      up(semid);
    }
  } else {
    while(1) {
      down(semid);
      critical("parent");
      up(semid);
    }
  }
}
