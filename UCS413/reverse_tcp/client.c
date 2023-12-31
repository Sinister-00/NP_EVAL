#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char sendline[100];
    char recvline[100];
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1)
    {
        printf("Enter a string: ");
        fgets(sendline, 100, stdin);
        send(sockfd, sendline, strlen(sendline), 0);

        bzero(recvline, 100);
        recv(sockfd, recvline, 100, 0);
        printf("Reversed string: %s\n", recvline);
    }

    close(sockfd);

    return 0;
}
