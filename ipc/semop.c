#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<assert.h>
#define KEY 12
#define NSEMS 8

main()
{
  int semid;
  struct sembuf sops1 = {0,1,0},sops2 = {0,-1,0};
  semid = semget(KEY,NSEMS,IPC_CREAT|0666);
  assert(semid != -1);
  
  semop(semid,&sops1,1);
  printf("after first semof....\n");
  
  // semop(semid,&sops2,1);
  //  printf("after second semop....\n");
  
  //  semop(semid,&sops2,1);
  //  printf("after third semop.....\n");
}