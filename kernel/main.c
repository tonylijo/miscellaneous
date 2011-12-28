#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
int main(int argc,char *argv[])
{
	int fd;
	char *buf = (char *) malloc(sizeof(char));
	*buf = 1;
	if((fd = open("/dev/parlelport",O_WRONLY)) < 0 ) {
		perror("cannot open /dev/parlelport");
		exit(errno);
	}
	while(1) {
		sleep(1);
		write(fd,buf,1);
		*buf <<= 1;
		if(!(*buf)) {
			*buf = 1;
		}
	}
	close(fd);
}
