#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "common.h"

#define MAX_NUM 2048

//ref: http://man7.org/linux/man-pages/man7/ip.7.html
#if 0
struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};

/* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* address in network byte order */
};
#endif

// argv["client", "8088"];
int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    char buf[MAX_NUM] = "abc";

    int port = LISTEN_PORT;
    if(argc > 1) {
        port = atoi(argv[1]);
    }
    printf("port: %d\n", port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);

    result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));

    printf("result is %d\n", result);

    if (result == -1)
    {
        perror("oops: client1");
        exit(1);
    } 
    else 
    {
        printf("connected to %s:%d!", "127.0.0.1", port);
    }
    write(sockfd, buf, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    printf("return from server = %s\n", buf);
    close(sockfd);
    exit(0);
}
