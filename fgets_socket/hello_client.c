#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[80];
	int str_len;
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);  //127.0.0.1
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0) 
		error_handling("connect() error!");

	do {
		fputs("문자열을 입력하세요! : ",stdout);
		fgets(message, sizeof(message), stdin);
		message[strlen(message)-1] = '\0';  //'\n' 제거 
		if(!strcmp(message,"quit"))  //"quit" 종료
			break;
		str_len=write(sock, message, strlen(message));
		if(str_len < 0)
				break;
		str_len=read(sock, message, sizeof(message)-1);
		if(str_len == 0)	//상대방 소켓 종료
				break;
		message[str_len] = '\0';
		if(str_len<0)
			error_handling("read() error!");

		printf("Message from server: %s(%d) \n", message,str_len);  
	} while(1);

	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
