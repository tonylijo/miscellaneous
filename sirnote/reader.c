#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<assert.h>

int main(int argc,char *argv[])
{
	int fd;
	fd = open("foo",O_RDONLY);
	printf("Hello, world\n");
}
