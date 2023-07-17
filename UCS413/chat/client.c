#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in server_addr;
    char message[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
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

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect Error");
        return 1;
    }

    printf("Connected to server\n");

    while (1)
    {
        printf("Enter a message: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        write(sock, message, strlen(message) + 1);

        if (strcmp(message, "exit") == 0)
            break;

        int n = read(sock, message, sizeof(message));
        if (n <= 0)
        {
            perror("read Error");
            break;
        }
        message[n] = '\0';
        printf("Message from server: %s\n", message);
    }

    close(sock);

    return 0;
}
