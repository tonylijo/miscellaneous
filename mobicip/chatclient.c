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

struct cmd {
	int clnt_port;
	int srv_port;
	char name[20];
	char ip[20];
};

void usage(void)
{
	printf("chatclient [options]\n-p for client port no \n -s for server <ip:port> \n -n <client name> \n ");
}

struct cmd *parse_cmd(int argc,char **argv)
{
	int i;
	struct cmd *tmp;
	char ip_buf[20],ser_port[20];
	tmp = (struct cmd *) malloc(sizeof(struct cmd));

	for(i = 1; i < argc;i++ ) {
		if(strcmp(argv[i],"-s") == 0) {
			char *new = argv[i+1];
			int j = 0;
			while(new[j] != ':') {
				ip_buf[j] = new[j++];
			}
			ip_buf[j++] = 0;
			int k = 0;
			while(new[j]) {
				ser_port[k++] = new[j++];
			}
			ser_port[k] = 0;
			strcpy(tmp->ip,ip_buf);
			tmp->srv_port = atoi(ser_port);
			i++;
		} else if(strcmp(argv[i],"-p") == 0) {
			tmp->clnt_port = atoi(argv[++i]);
		} else if(strcmp(argv[i],"-n") == 0) {
			strcpy(tmp->name,argv[++i]);
		} else {
			printf("unknown argument %s",argv[i]);
			usage();
			exit(-1);
		}
	}
	return tmp;
}	

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
	struct cmd *cmd;
	cmd = parse_cmd(argc,argv);
	printf("clnt_port = %d , clnt_name = %s , port = %d , ip = %s \n",
			cmd->clnt_port,cmd->name,cmd->srv_port,cmd->ip);
	
	client.sin_family = AF_INET;
	client.sin_port = htons(cmd->clnt_port);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(sock,(struct sockaddr *)&client,sizeof(struct sockaddr))) {
		perror("bind");
		exit(errno);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(cmd->srv_port);
	server.sin_addr.s_addr = inet_addr(cmd->ip);

	if(connect(sock,(struct sockaddr *) &server,sizeof(struct sockaddr))) {
		perror("connect");
		exit(errno);
	}
	send(sock,cmd->name,strlen(cmd->name) + 1,0);
	FD_ZERO(&allset);
	FD_ZERO(&rset);
	FD_SET(0,&allset);
	FD_SET(sock,&allset);
	maxfds = sock;
	printf(">>");
	fflush(stdout);
	while(1) {
		rset = allset;
		no_ready = select(maxfds + 1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(0,&rset)) {
			printf(">>");
			fflush(stdout);
			gets(buf);
			send(sock,buf,strlen(buf),0);
		}  
		if(FD_ISSET(sock,&rset)){
			bytes_read = recv(sock,buf1,MAXLINE,0);
			buf1[bytes_read] = 0;
			printf("%s",buf1);
		}
	}
}
