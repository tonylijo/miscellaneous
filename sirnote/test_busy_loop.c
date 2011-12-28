#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<assert.h>
int main(int argc,char *argv[])
{
	int fd,ret,n;
	char buf[10];
	fd = open("foo",O_RDONLY); 
	assert(fd > 0) ;
	while(1) {
		read(fd,buf,1);
		printf("%c\n",buf[0]);
	}
}
