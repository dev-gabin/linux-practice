#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int str_len;

	fd_set reads, temps;
	struct timeval timeout;
	int result;


	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[80];

	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(serv_sock < 0)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)
		error_handling("bind() error"); 

	if(listen(serv_sock, 5)<0)
		error_handling("listen() error");

	clnt_addr_size=sizeof(clnt_addr);  

	do {
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
		if(clnt_sock<0)
			error_handling("accept() error");  

		printf("클라이언트 접속(%s)\n",inet_ntoa(clnt_addr.sin_addr));
		FD_ZERO(&reads);
		FD_SET(fileno(stdin), &reads);
		FD_SET(clnt_sock, &reads);


		do { temps=reads;

			timeout.tv_sec=5;
			timeout.tv_usec=5000;

			result=select(clnt_sock+1, &temps, 0, 0, &timeout);

			if(result==-1)
			{
				puts("select() error!");
				break;
			}
			else if(result==0)
			{
				puts("Time-out!");
			}
			else
			{
				if(FD_ISSET(fileno(stdin), &temps))
				{
					fputs("문자열을 입력하세요!! : ", stdout);
					fgets(message, sizeof(message), stdin);
					message[strlen(message)-1]='\0';

					if(!strcmp(message, "quit"))
						break;

					str_len=write(clnt_sock,
							message,
							strlen(message));

					if(str_len<0)
						break;
				}
				else if(FD_ISSET(clnt_sock, &temps))
				{

					str_len = read(clnt_sock, message, sizeof(message)-1);
					if(!str_len)  //상대방 소켓 종료 
						break;
					else if(str_len < 0)
					{
						perror("read()");
						break;
					}
					message[str_len]='\0';
					printf("message:%s(%d)\n",message,str_len);
					write(clnt_sock, message, strlen(message));
						}
					}
				} while(1);
				close(clnt_sock);	
				printf("클라이언트 종료(%s)\n",inet_ntoa(clnt_addr.sin_addr));
			} while(1);
			close(serv_sock);
			return 0;
		}

		void error_handling(char *message)
		{
			fputs(message, stderr);
			fputc('\n', stderr);
			exit(2);}

