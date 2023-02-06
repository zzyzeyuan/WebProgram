#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short host_port=0x1234;
	unsigned short net_port;
	unsigned long host_addr=0x12345678;
	unsigned long net_addr;
	//htons 中h表示主机(host)字节序  n表示网络字节序   s表示short  htonl中l表示long
	// htons可以解释为“将short型数据从主机字节序转为网络字节序”
	net_port=htons(host_port);
    // host_port = 0x1234 小端序
    // net_port = 0x3412
	net_addr=htonl(host_addr);

    printf("Host ordered port: %#x \n", host_port);
	printf("Network ordered port: %#x \n", net_port);
	printf("Host ordered address: %#lx \n", host_addr);
	printf("Network ordered address: %#lx \n", net_addr);
	return 0;
}
