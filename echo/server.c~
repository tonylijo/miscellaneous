#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc,char *argv[])
{
  int main_fd,client_fd;
  struct sockaddr_in server,client;
  int len = sizeof(struct sockaddr);
  char in_buf[1024];
  int r_c;

  if((main_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    perror("socket:");
    exit(errno);
  }
  
  server.sin_family = AF_INET;
  server.sin_port = htons(5000);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  bzero(server.sin_zero,8);

  if(bind(main_fd,(struct sockaddr *) &server,sizeof(struct sockaddr)) < 0) {
    perror("bind");
    exit(errno);
  }

  if(listen(main_fd,5) < 0) {
    perror("listen");
    exit(errno);
  }

  while(1) {
    client_fd = accept(main_fd,(struct sockaddr *) &client,&len);
    
    r_c = read(client_fd,in_buf,1024);
    write(client_fd,in_buf,r_c);
  }
}
