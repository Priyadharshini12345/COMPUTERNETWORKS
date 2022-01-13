#include<stdio.h>                                                                                                                                                       
                                                                                                                                                                        
#include<stdlib.h>                                                                                                                                                      
                                                                                                                                                                        
#include<string.h>                                                                                                                                                      
                                                                                                                                                                        
#include<arpa/inet.h>                                                                                                                                                   
                                                                                                                                                                        
#include<sys/socket.h>                                                                                                                                                  
                                                                                                                                                                        
#include<sys/socket.h>                                                                                                                                                  
                                                                                                                                                                        
#include<unistd.h>                                                                                                                                                      
                                                                                                                                                                        
#define LOCALPORT 8090                                                                                                                                                  
                                                                                                                                                                        
#define SIZE 200                                                                                                                                                        

                                                                                                                                                                        
int main(){                                                                                                                                                             

        int sendbytes,recvbytes;                                                                                                                                        

        int sockfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                                        

        if(sockfd<0){                                                                                                                                                   
                                                                                                                                                                        
                printf("Error in creating socket\n");                                                                                                                   
                                                                                                                                                                        
                exit(0);                                                                                                                                                
                                                                                                                                                                        
        }                                                                                                                                                               

        struct sockaddr_in clientaddr;                                                                                                                                  
                                                                                                                                                                        
        memset(&clientaddr,0,sizeof(clientaddr));                                                                                                                       

        clientaddr.sin_port=htons(LOCALPORT);                                                                                                                           
        clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                              
        clientaddr.sin_family=AF_INET;                                                                                                                                  


        while(1){                                                                                                                                                       

                char buffer[SIZE];                                                                                                                                      
                char input[SIZE];                                                                                                                                       

                printf("<<Enter Hostname: ");                                                                                                                           
                                                                                                                                                                        
                scanf("%s",input);                                                                                                                                      
                                                                                                                                                                        
                sendbytes=sendto(sockfd,input,strlen(input)+1,0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));                                                      

                if(strncmp(input,"exit",4)==0) break;                                                                                                                   

                recvbytes=recvfrom(sockfd,buffer,sizeof(buffer),0,NULL,NULL);                                                                                           

                printf("Server IP Address: %s\n\n",buffer);                                                                                                             

        }                                                                                                                                                               

        close(sockfd);                                                                                                                                                  

        return 0;                                                                                                                                                       
}  