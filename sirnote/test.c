#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
int main()
{
	int fd,retval;
	char buf[] = "hello";
	
	fd = open("foo",O_RDONLY);
	
	if(fd < 0) {
		perror("read:");
		exit(errno);
	}
	
	printf("fd = %d \n",fd);
	retval = write(fd,buf,sizeof(buf));
	printf("write return value = %d \n",retval);
	if(retval < 0) perror("");
	retval = read(fd,buf,sizeof(buf));
	printf("read return value = %d \n",retval);
	if(retval < 0) perror("");
}

	
