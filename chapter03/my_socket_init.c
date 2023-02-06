#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    struct sockaddr_in svr_addr;
    //ip
    char * svr_ip = "127.0.0.1";
    //application port
    char * svr_port = "9091";
    memset(&svr_addr, 0, sizeof svr_addr);
    svr_addr.sin_family = AF_INET; // IPv4
    svr_addr.sin_addr.s_addr = inet_addr(svr_ip);
    svr_addr.sin_port = htons(atoi(svr_port));

    int svr_sock;
//    bind(svr_sock,(struct sockaddr*) svr_addr, sizeof(svr_addr));

    printf("%d\n", svr_addr.sin_addr.s_addr);
    printf("%d\n", svr_addr.sin_port);

    return 0;
}
