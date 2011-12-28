#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#define MAX 1024
int main(int argc,char *argv[])
{
	int fd,ret,n;
	char buf[MAX];

	fd = open("foo",O_RDONLY);
	if(fd < 0) {
		perror("open:");
		exit(errno);
	}
	
	printf("enter the read quantum \n");
	scanf("%d",&n);

	while((ret = read(fd,buf,n)) >  0) {
		write(1,buf,ret);
	}
	if(ret < 0) {
		fprintf(stderr,"Error in read \n");
		exit(1);
	}
	exit(0);
}	
