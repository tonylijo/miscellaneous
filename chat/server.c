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
  int ssock_fd,csock_fd;
  int len;
  int maxfds,no_ready,i,j;
  int bytes_read;
  char buf[MAXLINE];  
  fd_set rset,allset;
  if((ssock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    perror("socket");
    exit(errno);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(5000);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if(bind(ssock_fd,(struct sockaddr*) &server,sizeof(struct sockaddr))) {
      perror("bind");
      exit(errno);
  }

  if(listen(ssock_fd,5)) {
    perror("listen");
    exit(errno);
  }

  len = sizeof(struct sockaddr);

  FD_ZERO(&allset);
  FD_ZERO(&rset);
  FD_SET(ssock_fd,&allset);
  maxfds = ssock_fd;
  while(1) {
    rset = allset;
    if((no_ready = select(maxfds+1,&rset,NULL,NULL,NULL)) < 0) {
      perror("select");
      exit(errno);
    }
    for(i = 0; i <= maxfds; i++) {
      if(FD_ISSET(i,&rset)) {
	if(i == ssock_fd) {
	  if((csock_fd = accept(ssock_fd,(struct sockaddr *)&client,&len))<0) {
	    perror("accept");
	    exit(errno);
	  }
	  FD_SET(csock_fd,&allset);
	  printf("got a connection %d\n",csock_fd);
	  if(csock_fd > maxfds)
	    maxfds = csock_fd;
	} else {
	  if((bytes_read = recv(i,buf,MAXLINE,0)) <= 0) {
	    if(bytes_read == 0) {
 		printf("closing socket %d\n",i);
	      close(i);
	      FD_CLR(i,&allset);
	    } else {
	      perror("read");
	      exit(errno);
	    }
	  } else {
		 buf[bytes_read] = 0;
	    for(j = 0; j <= maxfds; j++) {
	      if(FD_ISSET(j,&allset) && (j != i) && (j != ssock_fd)) {
		      		printf("in ****j: %d\n",j);
				send(j,buf,bytes_read,0);
	     		 }
	    	
	    }
	  }
	}
      }
    }
  }
}	
