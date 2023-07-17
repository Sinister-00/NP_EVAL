#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main()
{
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in server_addr;
    char message[BUF_SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("socket Error");
        return 1;
    }

    printf("Socket created successfully\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    while (1)
    {
        printf("Enter a message: ");
        fgets(message, BUF_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';

        if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("sendto Error");
            return 1;
        }

        if (strcmp(message, "exit") == 0)
            break;

        int n = recvfrom(sock, message, BUF_SIZE, 0, NULL, NULL);
        if (n < 0)
        {
            perror("recvfrom Error");
            return 1;
        }
        message[n] = '\0';
        printf("Message from server: %s\n", message);
    }

    close(sock);

    return 0;
}
