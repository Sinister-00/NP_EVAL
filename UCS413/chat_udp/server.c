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
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    char message[BUF_SIZE];

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0)
    {
        perror("socket Error");
        return 1;
    }

    printf("Socket created successfully\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind Error");
        return 1;
    }

    printf("Binding successful\n");

    printf("Listening on %s:%d\n", ip, port);

    while (1)
    {
        client_addr_size = sizeof(client_addr);

        int n = recvfrom(server_socket, message, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_size);
        if (n < 0)
        {
            perror("recvfrom Error");
            return 1;
        }
        message[n] = '\0';
        printf("Message from client: %s\n", message);

        printf("Enter a response: ");
        fgets(message, BUF_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';

        if (sendto(server_socket, message, strlen(message), 0, (struct sockaddr *)&client_addr, client_addr_size) < 0)
        {
            perror("sendto Error");
            return 1;
        }

        if (strcmp(message, "exit") == 0)
            break;
    }

    close(server_socket);

    return 0;
}
