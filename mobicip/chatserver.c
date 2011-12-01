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
#define MAX_CLT 10

static char *cli_buf[4];

struct client_info {
	char name[20];
	int fd;
};

static struct client_info client_array[MAX_CLT];
static int clnt_count;


int find_array_index(int sock) 
{
	int i;
	for(i = 0; i < clnt_count; i++) {
		if(client_array[i].fd == sock) {
			return i;
		}
	}
	return -1;
}

int recv_hr(int sock,char *buf,fd_set *allset)
{
	int bytes_read;
	int index;
	if((bytes_read = recv(sock,buf,MAXLINE,0)) <= 0) {
		if(bytes_read == 0) {
			printf("closing socket %d \n",sock);
			close(sock);
			index = find_array_index(sock);
			client_array[index].name[0] = '\0';
			client_array[index].fd = 0;
			FD_CLR(sock,allset);
			return 0;
		} else {
			perror("read");
			exit(errno);
		}
	}
	return bytes_read;
}

void main_sock_hr(int socket,struct sockaddr *client,int *maxfd,
		fd_set *allset) 
{
	int csock_fd,len;
	len = sizeof(struct sockaddr);
	csock_fd = Accept(socket,client,&len);
	client_array[clnt_count].fd = csock_fd;
	recv(csock_fd,client_array[clnt_count++].name,20,0);
	FD_SET(csock_fd,allset);
	printf("got a connection on %d\n",csock_fd);
	if(csock_fd > *maxfd) 
		*maxfd = csock_fd;
}

void fill_cli_buf(char *buf)
{
	int i = 0;
	cli_buf[i++] = strtok(buf," ");
	while(cli_buf[i-1]) {
		if(i < 2) {
			cli_buf[i++] = strtok(NULL," ");
		} else {
			if(!(cli_buf[i++] = strtok(NULL,""))) {
				break;
			}
		}
	}
}	


int parse_cmd(int argc,char **argv) 
{
	if(argc < 3) {
		printf("usage : \n chatserver -p <port>\n");
		exit(-1);
	} else {
		if(strcmp(argv[1],"-p") == 0) {
			return atoi(argv[2]);
		} else {
			printf("unknown option %s \n",argv[1]);
			exit(-1);
		}	
	}
}	

int find_client(char *name)
{
	int i = 0;
	while(i < MAX_CLT) {
		if(strcmp(client_array[i++].name,name) == 0) {
			return client_array[i-1].fd;
		}
	}
	return -1;
}

void list(int sock)
{
	char buffer[MAXLINE] = {0};
	int j;
	for(j = 0; j <= clnt_count; j++) {
		printf("%s",client_array[j].name);
		strcat(buffer,client_array[j].name);
		strcat(buffer,"\n");
	}
	send(sock,buffer,strlen(buffer) + 1,0);
}

void talk(int sock)
{
	int fd;
	if((fd = find_client(cli_buf[1])) == -1) {
		send(sock,"no such client",15,0);
	} else {
		send(fd,cli_buf[2],strlen(cli_buf[2])+1,0);
	}
}

void quit(sock)
{
	int index;
	close(sock);
	index = find_array_index(sock);
	client_array[index].name[0] = '\0';
	client_array[index].fd = 0;
}

void process_cmd(int bytes_read,int sock,char *buf) 
{
	if(bytes_read > 0) {
		buf[bytes_read] = 0;
		fill_cli_buf(buf);
		if(strcmp(cli_buf[0],"list") == 0) {
			list(sock);
		} else if(strcmp(cli_buf[0],"talk") == 0) {
			talk(sock);
		}
	}
}

void main_handler(struct sockaddr *client,int ser_sock,int *maxfd,
		fd_set *allset,fd_set *rset) 
{
	
	int i;
	char buf[MAXLINE];
	int bytes_read;
	for(i = 0; i <= *maxfd; i++) {
		printf("%d\n",i);
		if(FD_ISSET(i,rset)) {
			if(i == ser_sock) {
				main_sock_hr(ser_sock,client,maxfd,allset);
			} else {
				bytes_read  = recv_hr(i,buf,allset);
				process_cmd(bytes_read,i,buf);
			}
		}
	}
}


int main(int argc,char *argv[])
{
	struct sockaddr_in server,client;
      	int ssock_fd,csock_fd;
	int maxfds,no_ready;
	int port;  
	port = parse_cmd(argc,argv);
	fd_set rset,allset;
  
	ssock_fd = create_tcp_socket();
  
	init_sockaddr_in(&server,AF_INET,port,"127.0.0.1");
	Bind(ssock_fd,(struct sockaddr *) &server);
	Listen(ssock_fd,5);

	FD_ZERO(&allset);
	FD_ZERO(&rset);
	FD_SET(ssock_fd,&allset);
	maxfds = ssock_fd;
	while(1) {
		rset = allset;
    
 		no_ready = Select(maxfds,&rset,NULL,NULL,NULL);
    
		main_handler((struct sockaddr *)&client,ssock_fd,&maxfds,&allset,&rset);
	}
}	
