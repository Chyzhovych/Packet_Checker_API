#ifndef PSOCKET_HPP
#define PSOCKET_HPP

#include <sys/socket.h>  
#include <sys/types.h>  
#include <resolv.h>  
#include <string.h>  
#include <stdlib.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <netdb.h> 
#include <arpa/inet.h>  


struct serverInfo  
{  
     int client_fd;  
     char ip[100];  
     char port[100];  
};  
 
 
 
int initSocket(int proxy_fd,struct sockaddr_in proxy_sd,char *proxy_port,char *ip,char *port);

void clientAccept(int proxy_fd,int client_fd,pthread_t tid,char *ip,char *port);

void *runSocket(void *vargp);



#endif // PSOCKET_HPP