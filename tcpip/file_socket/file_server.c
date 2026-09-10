#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	int file_fd;
    int str_len;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[100];
	
	if(argc!=3){
		printf("Usage : %s <port> <recv_file>\n", argv[0]);
		exit(1);
	}

	file_fd=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,
        S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if(file_fd<0)
    	error_handling("open() error");
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock<0)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error"); 
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock<0)
		error_handling("accept() error");
	
	
	do
	{
    	str_len=read(clnt_sock, message, sizeof(message));

    	if(str_len<0)
		{
        	error_handling("read() error");
		}
    		printf("read : %d\n", str_len);

   		if(str_len>0)
    	{	
        if(write(file_fd, message, str_len)==-1)
            error_handling("write() error");
   		}
	} while(str_len>0);

printf("Done..\n");
	if(close(file_fd)==-1)
    error_handling("close() error");

	if(close(clnt_sock)==-1)
    error_handling("close() error");

	if(close(serv_sock)==-1)
    error_handling("close() error");	
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
