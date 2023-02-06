#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len=0;
	int idx=0, read_len=0;
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() error!");

    // read(sock, &message[idx++], 1)表示在建立的数据传输方式sock中，读取message[idx]这一个字节大小的数据
    while (read_len = read(sock, &message[idx], 1))
    {
        if (read_len == -1)
            error_handling("read() error!");

        printf("print this line -> call read() function one time.\n");
        str_len += read_len;
        idx++;
    }
//	while((read_len=read(sock, &message[idx++], 1)))
//	{
//		if(read_len==-1)
//			error_handling("read() error!");
//
//		str_len+=read_len;
//	}

	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n", str_len);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
