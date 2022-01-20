#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <unistd.h>
#define SIZE 65535 //Max size buffer is 65535
#define ADDR "127.0.0.1"


int createSocket(int domain, int type, int protocol);

int initSocket(struct sockaddr_in *ptr_hints);

int Accept(int sockfd, struct sockaddr_in *ptr_hints,socklen_t *addrlen);

void proxyConnect(int client_fd);

void showMsg(int new_fd);

void closeServerConnection(int server_socket, int client_socket);

void *runSocket(void *vargp);

#endif // SOCKET_HPP
