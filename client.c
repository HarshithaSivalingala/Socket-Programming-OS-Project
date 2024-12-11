#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 1000
#define PORT 34354
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n;

    while (1)
    {
        bzero(buff, sizeof(buff));

        // Read user input
        printf("Enter the string (or type 'exit' to quit): ");
        fgets(buff, sizeof(buff), stdin);

        // If the user types "exit", send "I am exiting" to the server
        if (strncmp(buff, "exit", 4) == 0)
        {
            write(sockfd, "exit", strlen("exit"));
            printf("Exiting the client...\n");
            break;
        }

        // Send message to the server
        write(sockfd, buff, strlen(buff));

        // Read the server's response
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));

        // Print server's message
        printf("From server: %s\n", buff);
    }
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    // Set up server address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection to the server failed...\n");
        exit(0);
    }
    else
    {
        printf("Connected to the server..\n");
    }

    // Function to handle client-server communication
    func(sockfd);

    // Close the socket
    close(sockfd);
}
