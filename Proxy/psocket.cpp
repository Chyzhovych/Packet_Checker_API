#include <sys/socket.h>  
#include <sys/types.h>  
#include <resolv.h>  
#include <string.h>  
#include <stdlib.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <netdb.h> 
#include <arpa/inet.h> 
#include "psocket.hpp"




int initSocket(int proxy_fd,struct sockaddr_in proxy_sd,char *proxy_port,char *ip,char *port)
{
      // create a socket  
     if((proxy_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
     {  
          printf("\nFailed to create socket...");  
     } 

     printf("Proxy created\n");  
     memset(&proxy_sd, 0, sizeof(proxy_sd));  

     // set socket variables 

     proxy_sd.sin_family = AF_INET;  
     proxy_sd.sin_port = htons(atoi(proxy_port));  
     proxy_sd.sin_addr.s_addr = INADDR_ANY;  

     // Bind the socket  
     if((bind(proxy_fd, (struct sockaddr*)&proxy_sd,sizeof(proxy_sd))) < 0)  
     {  
           printf("Failed to bind a socket...");  
     }  
     // start listening to the port for new connections  
     if((listen(proxy_fd, SOMAXCONN)) < 0)  
     {  
          perror("Failed to listen");
          exit(EXIT_FAILURE);  
     }  
     printf("Waiting for connection...\n"); 

     return proxy_fd;

}

void clientAccept(int proxy_fd,int client_fd,pthread_t tid,char *ip ,char *port)
{
    //accept all client connections continuously  
     while(1)  
      {  
           client_fd = accept(proxy_fd, (struct sockaddr*)NULL ,NULL);  
           printf("Client no. %d is connected...\n",client_fd);  
           if(client_fd > 0)  
           {  
               //multithreading variables      
               struct serverInfo *item = (serverInfo*)malloc(sizeof(struct serverInfo));  
               item->client_fd = client_fd;  
               strcpy(item->ip,ip);  
               strcpy(item->port,port);  
               pthread_create(&tid, NULL, runSocket, (void *)item);  
               sleep(1);  
           }  
      }  
}


// A thread for each client request  
void *runSocket(void *vargp)  
{  
      struct serverInfo *info = (struct serverInfo *)vargp;  
      char buffer[65535];  
      int bytes = 0;  
      printf("Client: %d\n",info->client_fd);
      printf("%s ",info->ip);
      printf("%s ",info->port);    
   
      //code to connect to main server via this proxy server  
      int server_fd =0;  
      struct sockaddr_in server_sd;  

      // create a socket  
      server_fd = socket(AF_INET, SOCK_STREAM, 0);  

      if(server_fd < 0)  
      {  
          printf("Server socket not created...\n");  
      }  
      printf("Server socket created...\n");

      memset(&server_sd, 0, sizeof(server_sd));  
      // set socket variables  
      server_sd.sin_family = AF_INET;  
      server_sd.sin_port = htons(atoi(info->port));  
      server_sd.sin_addr.s_addr = inet_addr(info->ip);  

      //connect to main server from  proxy server  

      if((connect(server_fd, (struct sockaddr *)&server_sd, sizeof(server_sd))) < 0)  
      {  
          perror("Server connection not established...\n"); 
          exit(EXIT_FAILURE);
      }  
      printf("Server socket connected...\n");  

      while(1)  
      {  
           //receive data from client  
           memset(&buffer, '\0', sizeof(buffer));  
           bytes = read(info->client_fd, buffer, sizeof(buffer));  
           if(bytes < 0)  
           {  
               perror("Data is not receive...");
               exit(EXIT_FAILURE);
           }  
           else   
           {  
               // send data to main server  
               write(server_fd, buffer, sizeof(buffer));  
               //printf("client fd is : %d\n",c_fd);                    
               printf("From client :\n");                    
               fputs(buffer,stdout);       
               fflush(stdout);  
           }  
           
           //recieve response from server  
           memset(&buffer, '\0', sizeof(buffer));  
           bytes = read(server_fd, buffer, sizeof(buffer));  
           if(bytes < 0)  
           { 
               perror("Data is not receive...");
               exit(EXIT_FAILURE); 
           } 
                      
           else  
           {  
                // send response back to client  
                write(info->client_fd, buffer, sizeof(buffer));  
                printf("From server :\n");                    
                fputs(buffer,stdout);
                fflush(stdout);              
           }  
           
      };       
   return NULL;  
}  