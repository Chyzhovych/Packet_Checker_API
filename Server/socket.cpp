#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>  
#include <resolv.h> 
#include "checksum.hpp"

#define ADDR "127.0.0.1"
#define PORT 8080
#define BACKLOG 5
#define SIZE 65535 // Max size buffer 
#define TCP 2 // Protocol type



void *runSocket(void *vargp);  

int createSocket(int domain, int type, int protocol);

static void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

static void Listen(int socketfd, int backlog);

int initSocket(struct sockaddr_in *ptr_hints)
{
   int opt = 1;  
   int sockfd = createSocket(AF_INET,SOCK_STREAM,0);
 
   memset(ptr_hints,0,sizeof(ptr_hints));
   ptr_hints->sin_family = AF_INET;
   ptr_hints->sin_port = htons(PORT);
   ptr_hints->sin_addr.s_addr = INADDR_ANY;  

   // Forcefully attaching socket to the port 8080 
   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
   { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
   } 

   Bind(sockfd,(struct sockaddr*) ptr_hints, sizeof (*ptr_hints));

   Listen(sockfd,BACKLOG);
  
   return sockfd;
}


int createSocket(int domain, int type, int protocol)
{
   int socketfd = socket(domain, type, protocol);
 
   if(socketfd == -1)
   {
      perror("Socket error...");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Socket successfully created..\n" );
   }
   return socketfd;
}

static void Bind(int sockfd, const struct sockaddr *adr, socklen_t addrlen)
{
   int res = bind(sockfd, adr, addrlen);
   if (res == -1) 
   {
      perror("Bind failed");
      exit(EXIT_FAILURE);
   }
}

static void Listen(int socketfd, int backlog)
{
   int res = listen(socketfd, backlog);
   if(res == 0)
   {
      printf("Listening...\n");
   }
   else
   {
      perror("Listening failed...");
      exit(EXIT_FAILURE);
   }
 
}

int Accept(int sockfd, struct sockaddr_in *ptr_hints,socklen_t *addrlen) 
{

   int client_fd;
   client_fd = accept(sockfd,(struct sockaddr*) ptr_hints, addrlen);

   if(client_fd < 0)
   {
      perror("Not accept...");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Connection accept...\n");
   }

   return client_fd;

}

void proxyConnect(int client_fd)
{
   if(client_fd > 0)  
   {  
       
      printf("Proxy connected...\n");     
      pthread_t tid;  
      // pass client fd as a thread parameter 
     while(1){
      pthread_create(&tid, NULL, runSocket, (void *)client_fd);
     }
      
   }  

}

void showMsg(int new_fd)
{
    char buff[SIZE] = {0};
    bzero(buff, SIZE);
      int nread = read(new_fd, buff, SIZE);
      if(nread == -1)
      {
         perror("Read failed...");
         exit(EXIT_FAILURE);
      }
      if (nread == 0)  
      {
         printf("\nEnd of file...");
      }
      else
      {
        printf("Client msg: %s", buff);
      } 
}


void closeServerConnection(int server_socket, int client_socket)
{
   close(client_socket);
   close(server_socket);
   printf("\nServer connection close...\n");  

}

void *runSocket(void *vargp)  
 {  
   int c_fd =(int)vargp; // get client fd from arguments passed to the thread  
   char buffer[SIZE];  
   int bytes = 0;  
   while(1)  
   {  
      //receive data from client  
      memset(&buffer,'\0',sizeof(buffer));  
      bytes = read(c_fd, buffer, sizeof(buffer));

      // Calculating packet checksum

      checksum(buffer,SIZE,TCP);

      calculateChecksum(buffer);
         
      if(bytes < 0)  
      {  
         perror("Read error...");
         exit(EXIT_FAILURE);  
      }  
      else if(bytes == 0)  
      {  
         printf("This block works...");
      }  
      else  
      {  
         //send the same data back to client  
         // implement echo server
         write(c_fd, buffer, sizeof(buffer));  
         //printf("Client fd is : %d\n",c_fd);                 
         printf("From client:\n", buffer);                    
         fputs(buffer,stdout); 
              
      }  
     fflush(stdout);  
   };       
   return NULL;  
 }  





