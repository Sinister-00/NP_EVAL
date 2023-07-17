#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 22000
#define MAXLINE 100

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char reversed[MAXLINE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1)
    {
        printf("Enter a string: ");
        fgets(buffer, sizeof(buffer), stdin);

        sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

        int n = recvfrom(sockfd, (char *)reversed, MAXLINE, 0, NULL, NULL);
        reversed[n] = '\0';

        printf("Reversed string: %s\n", reversed);
    }

    return 0;
}
