#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define PORT 22000
#define MAXLINE 100

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char reversed[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Server listening on port %d\n", PORT);

    while (1)
    {
        socklen_t len = sizeof(cliaddr);
        bzero(buffer, sizeof(buffer));

        int n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';

        printf("Received: %s", buffer);

        int k = 0;
        int i = strlen(buffer) - 2;
        while (i >= 0)
        {
            reversed[k++] = buffer[i--];
        }
        reversed[k] = '\0';

        printf("Reversed string: %s\n", reversed);

        sendto(sockfd, (const char *)reversed, strlen(reversed), 0, (const struct sockaddr *)&cliaddr, len);
    }

    return 0;
}
