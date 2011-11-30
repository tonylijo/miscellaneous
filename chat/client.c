#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>
#include<sys/select.h>
#define MAXLINE 1024

int main(int argc,char *argv[])
{
	struct sockaddr_in server,client;
	int sock,len,count,connected;
	fd_set allset,rset;
	int maxfds;
	int bytes_read;
	int no_ready;
	char buf[MAXLINE],buf1[MAXLINE];
	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("socket");
		exit(errno);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(5000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sock,(struct sockaddr *) &server,sizeof(struct sockaddr))) {
		perror("connect");
		exit(errno);
	}

	FD_ZERO(&allset);
	FD_ZERO(&rset);
	FD_SET(0,&allset);
	FD_SET(sock,&allset);
	maxfds = sock;
	while(1) {
		rset = allset;
		no_ready = select(maxfds + 1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(0,&rset)) {
			gets(buf);
			send(sock,buf,strlen(buf),0);
		}  
		if(FD_ISSET(sock,&rset)){
			bytes_read = recv(sock,buf1,MAXLINE,0);
			buf1[bytes_read] = 0;
			printf("%s\n",buf1);
		}
	}
}
