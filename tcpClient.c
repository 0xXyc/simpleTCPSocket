#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{

    // Create socket()
    int ntwrk_socket = socket(AF_INET, SOCK_STREAM, 0);         // Socket descriptor with socket(), AF_INET = IPv4, SOCK_STREAM = TCP, 0 means operate on the IP layer of our transport layer.

    // Specify address for socket in a structure
    char * ip = "172.217.2.206";
    struct sockaddr_in server_addr;                          // Declare structure for AF_INET
    server_addr.sin_family = AF_INET;                        // Establish the family for the address
    server_addr.sin_port = htons(80);                     // htons() is taking the port number we specified and making sure that port number is being transmitted across the network in correct network byte order
    //server_addr.sin_addr.s_addr = INADDR_ANY;                // INADDR_ANY means that our socket will be established on any IP interface on our system -- This is the same as 0.0.0.0
    inet_pton(AF_INET, ip, &server_addr.sin_addr.s_addr);

    // connect() to remote socket
    int connection_status = connect(ntwrk_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));

    // Check to ensure connection was successful -- Implemented error handling as well (-1 will indicate an error, 0 indicates success)

        if (connection_status == 0)
        {
            printf("Connection to remote socket was successful.\n\n");
        }

        else
        { 
            printf("Connection to remote socket failed, please try again.\n");
        }
        
    // Send message to HTTP server
    char* mess = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(ntwrk_socket, mess, strlen(mess), 0);

    // recv() data from the remote client
    char server_response[256];
    recv(ntwrk_socket, &server_response, sizeof(server_response), 0);

    // Print server's response
    printf("Server's Response: \n\n%s\n\n\n", server_response);

    // close() socket
    printf("Closing socket.\n");
    close(ntwrk_socket);

    return 0;

}
