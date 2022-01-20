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
  

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "8080"
#define PROXY_PORT "5000"
#define PROXY_IP "127.0.0.1"

 
 int main()  
 {  
     pthread_t tid;  
     char port[100],ip[100];  
     char *hostname = SERVER_IP;    
     char proxy_port[100];  
    
     strcpy(ip,SERVER_IP); // server ip  
     strcpy(port,SERVER_PORT);  // server port  
     strcpy(proxy_port,PROXY_PORT); // proxy port  

     printf("Server IP : %s and port %s " , ip,port);   
     printf(" Proxy port is %s",proxy_port);        
     printf("\n");  

     //socket variables  
     int proxy_fd =0, client_fd=0;  
     struct sockaddr_in proxy_sd;  

     // add this line only if server exits when client exits  
     signal(SIGPIPE,SIG_IGN);  

     proxy_fd = initSocket(proxy_fd,proxy_sd,proxy_port,ip,port);

     clientAccept(proxy_fd, client_fd, tid, ip, port);
   
      return 0;  
 } 

