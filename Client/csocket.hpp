#ifndef CSOCKET_HPP
#define CSOCKET_HPP

int createSocket(int domain, int type, int protocol);

int Connect(int server_socket, int connect_socket,struct sockaddr_in *ptr_hints);

void sendMsg(int sd);

void closeClientConnection(int client_socket, int connect_socket);


#endif // CSOCKET_H