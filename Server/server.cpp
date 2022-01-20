#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.hpp"




int main()
{
    struct sockaddr_in *hints;
    socklen_t addrlen = sizeof(hints);
    int server_socket = 0;
    int client_socket = 0;

    // Create socket

    server_socket = initSocket(hints);

    // Create new socket descriptor

    client_socket = Accept(server_socket,hints,&addrlen);

    proxyConnect(client_socket);

    closeServerConnection(server_socket,client_socket);


    return 0;
}