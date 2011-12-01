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

int create_tcp_socket()
{
	int ssock_fd;
	if((ssock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("socket");
		exit(errno);
	}
	return ssock_fd;
}

void Bind(int sock_fd,struct sockaddr *server) 
{
	if(bind(sock_fd,server,sizeof(struct sockaddr))) {
		perror("bind");
		exit(errno);
	}
}

void Listen(int sock_fd,int no_listeners)
{
	if(listen(sock_fd,no_listeners)) {
		perror("listen");
		exit(errno);
	}
}

int Accept(int sock_fd,struct sockaddr *client,int *len)
{	int c;
	if((c = accept(sock_fd,client,len)) < 0) {
		perror("accept");
		exit(errno);
	}
	return c;
}

int Select(int maxfd,fd_set *rset,fd_set *wset,fd_set *errset) 
{
	int no_ready;
	if((no_ready = select(maxfd + 1,rset,wset,errset,NULL)) < 0) {
		perror("select");
		exit(errno);
	}
	return no_ready;
}

void init_sockaddr_in(struct sockaddr_in *server,int FAM,int port,char *ip)
{
	server->sin_family = FAM;
	server->sin_port = htons(port);
	server->sin_addr.s_addr = inet_addr("127.0.0.1");
}
