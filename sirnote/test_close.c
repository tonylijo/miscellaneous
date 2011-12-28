#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	int fd;
	char buf[] = "hello";
	
	fd = open("foo",O_RDONLY);
	if(fd < 0) {
		perror("open:");
		exit(errno);
	}
	
	close(fd);
}
