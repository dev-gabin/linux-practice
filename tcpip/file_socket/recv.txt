#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	int file_fd;
	struct sockaddr_in serv_addr;
	char message[100];
	int str_len;
	
	if(argc!=4){
		printf("Usage : %s <IP> <port> <send_file>\n", argv[0]);
		exit(1);
	}
	
	file_fd=open(argv[3], O_RDONLY);
	if(file_fd<0)
	{	
    printf("<%s> file open error\n", argv[3]);
    perror("open()");
    exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock<0)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() error!");
	
	do
	{
    	str_len=read(file_fd, message, sizeof(message));

    	if(str_len<0)
		{
        	error_handling("read() error");
		}
   		if(str_len>0)
    	{
        	if(write(sock, message, str_len)==-1)
            	error_handling("write() error");
    	}
	} while(str_len>0);

printf("Done..\n");
	if(close(file_fd)<0)
    error_handling("close() error");

	if(close(sock)<0)
    error_handling("close() error");
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
