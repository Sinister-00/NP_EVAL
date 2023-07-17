#include <stdio.h>      // for printf() and fprintf()
#include <sys/socket.h> // for socket(), bind(), sendto(), and recvfrom()
#include <sys/types.h>  // for socket(), bind(), sendto(), and recvfrom()
#include <netdb.h>      // for getaddrinfo()
#include <arpa/inet.h>  // for inet_ntop()
#include <unistd.h>     // for close()
#include <string.h>     // for memset()

int main()
{
  char recv[100];                      // buffer to store the received message
  char sendline[100];       // buffer to store the message to be sent
  int sockfd;               // socket file descriptor
  int broadcast = 1;        // variable to enable broadcast
  struct sockaddr_in saddr; // structure to store the address of the sender

  sockfd = socket(AF_INET, SOCK_DGRAM, 0); // creating a socket for UDP connection

  bzero(&saddr, sizeof(saddr));                                                // clearing the saddr buffer
  saddr.sin_family = AF_INET;                                                  // setting the family of the address
  saddr.sin_port = htons(22000);                                               // setting the port number of the address
  saddr.sin_addr.s_addr = inet_addr("172.16.59.6");                          // setting the ip address of the sender to broadcast address (look at the ipconfig output)
  setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)); // enabling broadcast on the socket

  bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)); // binding the socket to the address

  for (;;) // infinite loop
  {
    printf("Message to be sent: ");
    scanf("%s", sendline); // reading the message to be sent from the user
    sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&saddr, sizeof(saddr)); // sending the message to the broadcast address
  }

  // The close() call is removed from here, allowing the loop to continue indefinitely.
}
