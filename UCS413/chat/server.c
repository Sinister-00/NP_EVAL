#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    char *ip = "127.0.0.1";
    int port = 5566;
    int server_socket;
    int client_socket;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;
    char message[1024];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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

    if (listen(server_socket, 5) < 0)
    {
        perror("listen Error");
        return 1;
    }

    printf("Listening on %s:%d\n", ip, port);

    while (1)
    {
        client_addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_socket < 0)
        {
            perror("accept Error");
            return 1;
        }
        printf("Client connected\n");

        while (1)
        {
            int n = read(client_socket, message, sizeof(message));
            if (n <= 0)
            {
                perror("read Error");
                break;
            }
            message[n] = '\0';
            printf("Message from client: %s\n", message);

            printf("Enter a response: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0';

            write(client_socket, message, strlen(message) + 1);

            if (strcmp(message, "exit") == 0)
                break;
        }

        close(client_socket);
    }

    close(server_socket);

    return 0;
}
