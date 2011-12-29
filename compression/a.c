#include<zlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd,count;
	char src_buf[4096];
	char dest_buf[4096];
	unsigned long dest_len = 4096;
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		perror("open");
		exit(errno);
	}
	if((count = read(fd,src_buf,4096)) < 0) {
		perror("read");
		exit(errno);
	}
	if(compress(dest_buf,&dest_len,src_buf,count) == Z_OK) 
		printf("Success\n");
	else {
		perror("compress");
		exit(errno);
	}

	close(fd);

	if((fd = open(argv[2],O_WRONLY|O_CREAT,0777)) < 0) {
		perror("open");
		exit(errno);
	}
	
	if(write(fd,dest_buf,dest_len)< 0) {
		perror("write");
		exit(errno);
	}
}
#include<zlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd,count;
	char src_buf[4096];
	char dest_buf[4096];
	unsigned long dest_len = 4096;
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		perror("open");
		exit(errno);
	}
	if((count = read(fd,src_buf,4096)) < 0) {
		perror("read");
		exit(errno);
	}
	if(compress(dest_buf,&dest_len,src_buf,count) == Z_OK) 
		printf("Success\n");
	else {
		perror("compress");
		exit(errno);
	}

	close(fd);

	if((fd = open(argv[2],O_WRONLY|O_CREAT,0777)) < 0) {
		perror("open");
		exit(errno);
	}
	
	if(write(fd,dest_buf,dest_len)< 0) {
		perror("write");
		exit(errno);
	}
}
#include<zlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd,count;
	char src_buf[4096];
	char dest_buf[4096];
	unsigned long dest_len = 4096;
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		perror("open");
		exit(errno);
	}
	if((count = read(fd,src_buf,4096)) < 0) {
		perror("read");
		exit(errno);
	}
	if(compress(dest_buf,&dest_len,src_buf,count) == Z_OK) 
		printf("Success\n");
	else {
		perror("compress");
		exit(errno);
	}

	close(fd);

	if((fd = open(argv[2],O_WRONLY|O_CREAT,0777)) < 0) {
		perror("open");
		exit(errno);
	}
	
	if(write(fd,dest_buf,dest_len)< 0) {
		perror("write");
		exit(errno);
	}
}
#include<zlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd,count;
	char src_buf[4096];
	char dest_buf[4096];
	unsigned long dest_len = 4096;
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		perror("open");
		exit(errno);
	}
	if((count = read(fd,src_buf,4096)) < 0) {
		perror("read");
		exit(errno);
	}
	if(compress(dest_buf,&dest_len,src_buf,count) == Z_OK) 
		printf("Success\n");
	else {
		perror("compress");
		exit(errno);
	}

	close(fd);

	if((fd = open(argv[2],O_WRONLY|O_CREAT,0777)) < 0) {
		perror("open");
		exit(errno);
	}
	
	if(write(fd,dest_buf,dest_len)< 0) {
		perror("write");
		exit(errno);
	}
}
#include<zlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd,count;
	char src_buf[4096];
	char dest_buf[4096];
	unsigned long dest_len = 4096;
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		perror("open");
		exit(errno);
	}
	if((count = read(fd,src_buf,4096)) < 0) {
		perror("read");
		exit(errno);
	}
	if(compress(dest_buf,&dest_len,src_buf,count) == Z_OK) 
		printf("Success\n");
	else {
		perror("compress");
		exit(errno);
	}

	close(fd);

	if((fd = open(argv[2],O_WRONLY|O_CREAT,0777)) < 0) {
		perror("open");
		exit(errno);
	}
	
	if(write(fd,dest_buf,dest_len)< 0) {
		perror("write");
		exit(errno);
	}
}
#include<zlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd,count;
	char src_buf[4096];
	char dest_buf[4096];
	unsigned long dest_len = 4096;
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		perror("open");
		exit(errno);
	}
	if((count = read(fd,src_buf