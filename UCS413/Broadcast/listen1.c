#include <stdio.h>      // for printf() and fprintf()
#include <sys/socket.h> // for socket(), bind(), sendto(), and recvfrom()
#include <sys/types.h>  // for socket(), bind(), sendto(), and recvfrom()
#include <netdb.h>      // for getaddrinfo()
#include <arpa/inet.h>  // for inet_ntop()
#include <unistd.h>     // for close()
#include <string.h>     // for memset()

int main()
{
    char recvline[100];                      // buffer to store the received message
    int sockfd;                              // socket file descriptor
    int broadcast = 1;                       // variable to enable broadcast
    struct sockaddr_in saddr, caddr;         // structure to store the address of the sender
    socklen_t caddrsize = sizeof(caddr);     // size of the caddr structure
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // creating a socket for UDP connection

    bzero(&saddr, sizeof(saddr));                                                // clearing the saddr buffer
    saddr.sin_family = AF_INET;                                                  // setting the family of the address
    saddr.sin_port = htons(22000);                                               // setting the port number of the address
    saddr.sin_addr.s_addr = INADDR_ANY;                                          // setting the ip address of the sender
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &broadcast, sizeof(broadcast)); // enabling broadcast on the socket

    bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)); // binding the socket to the address

    for (;;) // infinite loop
    {
        bzero(recvline, 100);                                                      // clearing the recvline buffer
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr *)&caddr, &caddrsize); // receiving the message from the sender
        printf("Received %s\n", recvline);                                           // printing the received message
    }

    // The close() call is removed from here, allowing the loop to continue indefinitely.
}
