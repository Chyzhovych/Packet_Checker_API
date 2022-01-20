#include "csocket.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>



int main()
{

    struct sockaddr_in hints;
    int client_socket = 0; 
    int connect_socket = 0;
  
    client_socket = createSocket(AF_INET,SOCK_STREAM,0);

    connect_socket = Connect(client_socket, connect_socket,&hints);

    sendMsg(client_socket);

    closeClientConnection(client_socket,connect_socket);

    return 0;
}