#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 1000
#define PORT 34354
#define SA struct sockaddr

void *handle_client(void *arg)
{
    int connfd = *(int *)arg;
    char buff[MAX];
    int n;

    while (1)
    {
        bzero(buff, sizeof(buff));

        // Read message from client
        read(connfd, buff, sizeof(buff));

        // If client sends "exit", terminate communication
        if (strncmp(buff, "exit", 4) == 0)
        {
            // Log the message "A client exited"
            printf("A client exited\n");

            // Send a confirmation message to the client
            // char exit_msg[] = "Server: Client has exited.";
            // write(connfd, exit_msg, strlen(exit_msg));

            break;  // Break the loop and close the connection for this client
        }

        // Print the message received from the client
        printf("From client: %s", buff);

        // Respond back to client
        bzero(buff, sizeof(buff));
        printf("Enter message for client: ");
        fgets(buff, sizeof(buff), stdin);  // Get server's response message
        write(connfd, buff, strlen(buff));  // Send it to the client
    }

    close(connfd);  // Close the connection to the client
    pthread_exit(NULL);  // Exit the thread when done
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    pthread_t tid;

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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client
    servaddr.sin_port = htons(PORT);

    // Bind the socket
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Socket binding failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    // Listen for client connections
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }

    // Accept connections from clients
    len = sizeof(cli);
    while (1)
    {
        connfd = accept(sockfd, (SA *)&cli, &len);
        if (connfd < 0)
        {
            printf("Server accept failed...\n");
            exit(0);
        }
        else
        {
            printf("Server accepted the client...\n");
        }

        // Create a new thread for each client
        if (pthread_create(&tid, NULL, handle_client, (void *)&connfd) != 0)
        {
            printf("Thread creation failed...\n");
        }
    }

    close(sockfd);  // Close server socket when done
}
