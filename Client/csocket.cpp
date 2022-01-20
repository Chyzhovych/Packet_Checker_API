#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define SIZE 65535 //Max size buffer is 65535
#define PORT 5000
#define ADDR "127.0.0.1"


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

int Connect(int client_socket, int connect_socket,struct sockaddr_in *ptr_hints)
{
   memset(ptr_hints ,0,sizeof(*ptr_hints));
   // Assign INFO
   ptr_hints->sin_family = AF_INET;
   ptr_hints->sin_port = htons(PORT);
   ptr_hints->sin_addr.s_addr = inet_addr(ADDR);

   connect_socket = connect(client_socket,(struct sockaddr*) ptr_hints, sizeof(*ptr_hints));

   if(connect_socket == -1)
   {
      perror("Connection with the server is failed...\n");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Connection is successfully...\n");
   }
   return connect_socket;
}


void sendMsg(int sd)
{
   while(1)  
   {  
      char buffer[SIZE];
      printf("Enter your message: ");  
      fgets(buffer, sizeof(buffer), stdin);  
      write(sd, buffer, sizeof(buffer));  
      printf("\nServer response:\n\n");  
      read(sd, buffer, sizeof(buffer));  
      fputs(buffer, stdout);  
      
   };  
}


void closeClientConnection(int client_socket, int connect_socket)
{
   close(client_socket);
   close(connect_socket);
   printf("Client is disconect...\n");
}
