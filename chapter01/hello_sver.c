#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[]="Hello World!";
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

    // step 1    调用socket创建套接字   int socket(int domain, int type, int protocol)

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	//bind()	分配IP地址和端口号
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error"); 
	//调用listen()使其套接字可以接受客户端的连接
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr); 
	// 调用accept() 受理客户端连接请求
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");  
	
	write(clnt_sock, message, sizeof(message));

    // ssize_t  size_t -> 元数据类型 在sys/types.h中一般由typedef声明定义
    // 在项目中，为了给基本数据类型赋予别名，一般会添加大量typedef声明；
    // 而为了与程序员定义的新数据类型加以区分，操作系统定义的数据类型会添加后缀_t


    /*
     * write函数原型：
     * ssize_t write (int fd, const void * buf, size_t nbytes)
     * fd -> 文件描述符
     * buf 保存要传输的数据的缓冲地址
     * nbytes 是要传输的数据的字节数*/
	close(clnt_sock);
    /*
     * int close ( int fd)*/
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
