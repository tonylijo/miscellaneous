#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<assert.h>
#include"foo.h"
int main(int argc,char *argv[])
{
	int r;
	int fd;
	fd = open("foo",O_RDONLY);
	assert(fd > 0) ;
	r = ioctl(fd,FOO_IOCTL1);
	assert(fd > 0);
	r = ioctl(fd,FOO_IOCTL2);
	assert(fd > 0);
}	
